crawl : crawl.cpp CrawlerNorm.cpp
	g++ crawl.cpp CrawlerNorm.cpp -lcurl -o crawl
clean :
	rm -rf crawl
cleanbak :
	rm -rf *~