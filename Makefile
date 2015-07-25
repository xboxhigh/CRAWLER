gather: HTTPCrawler.cpp sockFunc.cpp globalFunc.cpp urlListManage.cpp
	g++ HTTPCrawler.cpp sockFunc.cpp pageGathering.cpp globalFunc.cpp urlListManage.cpp -lm /usr/local/lib/libcurl.so -o HTTPCRAWLER

gather1: HTTPCrawler.cpp sockFunc.cpp globalFunc.cpp urlListManage.cpp
	g++ HTTPCrawler.cpp sockFunc.cpp pageGathering.cpp globalFunc.cpp urlListManage.cpp -lm /usr/local/lib/libcurl.so -o HTTPCRAWLER1

gather2: HTTPCrawler.cpp sockFunc.cpp globalFunc.cpp urlListManage.cpp
	g++ HTTPCrawler.cpp sockFunc.cpp pageGathering.cpp globalFunc.cpp urlListManage.cpp -lm /usr/local/lib/libcurl.so -o HTTPCRAWLER2

gather3: HTTPCrawler.cpp sockFunc.cpp globalFunc.cpp urlListManage.cpp
	g++ HTTPCrawler.cpp sockFunc.cpp pageGathering.cpp globalFunc.cpp urlListManage.cpp -lm /usr/local/lib/libcurl.so -o HTTPCRAWLER3

gather4: HTTPCrawler.cpp sockFunc.cpp globalFunc.cpp urlListManage.cpp
	g++ HTTPCrawler.cpp sockFunc.cpp pageGathering.cpp globalFunc.cpp urlListManage.cpp -lm /usr/local/lib/libcurl.so -o HTTPCRAWLER4
        
gather5: HTTPCrawler.cpp sockFunc.cpp globalFunc.cpp urlListManage.cpp
	g++ HTTPCrawler.cpp sockFunc.cpp pageGathering.cpp globalFunc.cpp urlListManage.cpp -lm /usr/local/lib/libcurl.so -o HTTPCRAWLER5
                        
extract: HTTPParser.cpp urlExtracting.cpp globalFunc.cpp sockFunc.cpp
	g++ HTTPParser.cpp urlExtracting.cpp globalFunc.cpp sockFunc.cpp -o LinksExtract

url: URLPoolManager.cpp sockFunc.cpp globalFunc.cpp urlListManage.cpp
	g++ URLPoolManager.cpp sockFunc.cpp globalFunc.cpp urlListManage.cpp -o URLManager

client: clientTest.cpp sockFunc.cpp
	g++ clientTest.cpp sockFunc.cpp globalFunc.cpp -o client

server: ControlCenter.cpp sockFunc.cpp
	g++ ControlCenter.cpp sockFunc.cpp globalFunc.cpp -o server
cleanbak:
	rm -rf ./*~	