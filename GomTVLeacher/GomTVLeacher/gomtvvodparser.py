import requests
from HTMLParser import HTMLParser
from time import strptime, strftime
import GomTv

GOM_BASE_URL = 'http://www.gomtv.net'
GOM_VOD_URL =  'http://www.gomtv.net/videos/index.gom'

IS_GOM_VOD_LINK_TAG  = lambda tag, attrs : tag == 'a'   and ('class', 'vod_link') in attrs
IS_GOM_VOD_THUMB_TAG = lambda tag, attrs : tag == 'img' and ('class', 'v_thumb')  in attrs
IS_GOM_VOD_STAT_TAG  = lambda tag, attrs : tag == 'li'  and ('class', 'v_date')   in attrs

IS_GOM_VOD_LIST_TAG  = lambda tag, attrs : tag == 'ul'  and ('id', 'vodList')     in attrs

GOM_VOD_DATE_FORMAT  = '%b. %d, %Y'

class GomVodsHTMLParser(HTMLParser) :

    def __init__(self) :
        HTMLParser.__init__(self)
        self.gomVods = list()

        self.canBeDate = False
        self.captureDate = False

    def handle_starttag(self, tag, attrs):
        attrsDict = dict(attrs)

        if IS_GOM_VOD_LINK_TAG(tag, attrs) :
            name = attrsDict['title']
            vodLink = '%s%s' % (GOM_BASE_URL, attrsDict['href'])
            gomVod = GomTv.GomTvVod(name.encode('utf-8'), vodLink.encode('utf-8'))
            self.gomVods.append(gomVod)

        elif IS_GOM_VOD_THUMB_TAG(tag, attrs) :
            thumbLink = attrsDict['alt'], attrsDict['src']
            #self.gomVods[-1].thumbLink = thumbLink

        elif IS_GOM_VOD_STAT_TAG(tag, attrs) :
            self.canBeDate = True

        elif self.canBeDate and tag == 'strong' :
            self.captureDate = True

    def handle_endtag(self, tag) :
        if self.canBeDate and tag == 'li' :
            self.canBeDate = False
        if self.captureDate and tag == 'strong' :
            self.captureDate = False
        
    def handle_data(self, data) :
        if self.captureDate :
            try : 
                date = strptime(data, GOM_VOD_DATE_FORMAT)
                self.gomVods[-1].date = strftime('%B %D %Y', date)
            except ValueError:
                pass

class GomSingleVodHTMLParser(HTMLParser) :

    def __init__(self, gomVod) :
        HTMLParser.__init__(self)
        self.gomVod = gomVod
        self.countSets = False

    def handle_starttag(self, tag, attrs) :

        if IS_GOM_VOD_LIST_TAG(tag, attrs) :
            self.countSets = True

        elif self.countSets and tag == 'a' :
            attrsDict = dict(attrs)
            self.gomVod.sets.append(attrsDict['title'])

    def handle_endtag(self, tag) :
        if self.countSets and tag == 'ul' :
            self.countSets = False

def getGomVods() :
    response = requests.get(GOM_VOD_URL)
    html = response.text.replace('class="""', 'class=""') # WTF GOM ...

    parser = GomVodsHTMLParser()
    parser.feed(html)

    return parser.gomVods

def setVodInfos(vod) :
    html = requests.get(vod.vodLink)
    parser = GomSingleVodHTMLParser(vod)
    parser.feed(html.text)