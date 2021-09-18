#include "../../IHTTPMessage.interface/Request.class/Request.hpp"
#include "../UnitTestsHeader.h"

void RequestTestOne() {
	Request request("GET / HTTP/1.1\n"
					"Host: 127.0.0.1:1111\n"
					"Connection: keep-alive\n"
					"sec-ch-ua: \"Chromium\";v=\"88\", \"Google Chrome\";v=\"88\", \";Not A Brand\";v=\"99\"\n"
					"sec-ch-ua-mobile: ?0\n"
					"Upgrade-Insecure-Requests: 1\n"
					"User-Agent: Mozilla/5.0 (Macintosh; Intel Mac OS X 10_14_6) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/88.0.4324.150 Safari/537.36\n"
					"Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3;q=0.9\n"
					"Sec-Fetch-Site: none\n"
					"Sec-Fetch-Mode: navigate\n"
					"Sec-Fetch-User: ?1\n"
					"Sec-Fetch-Dest: document\n"
					"Accept-Encoding: gzip, deflate, br\n"
					"Accept-Language: ru-RU,ru;q=0.9,en-US;q=0.8,en;q=0.7,fr;q=0.6\n\n");
	std::vector<std::string> headerSucsess = { "Host: 127.0.0.1:1111",
											   "Connection: keep-alive",
											   "sec-ch-ua: \"Chromium\";v=\"88\", \"Google Chrome\";v=\"88\", \";Not A Brand\";v=\"99\"",
											   "sec-ch-ua-mobile: ?0",
											   "Upgrade-Insecure-Requests: 1",
											   "User-Agent: Mozilla/5.0 (Macintosh; Intel Mac OS X 10_14_6) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/88.0.4324.150 Safari/537.36",
											   "Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3;q=0.9",
											   "Sec-Fetch-Site: none",
											   "Sec-Fetch-Mode: navigate",
											   "Sec-Fetch-User: ?1",
											   "Sec-Fetch-Dest: document",
											   "Accept-Encoding: gzip, deflate, br",
											   "Accept-Language: ru-RU,ru;q=0.9,en-US;q=0.8,en;q=0.7,fr;q=0.6"};
	const s_startline &startline = request.getStartLine();
	const s_headers &headers = request.getHeaders();
	const s_bodyes &bodyes = request.getBodyes();
	UnitCompare(startline.method, "GET");
	UnitCompare(startline.target, "/");
	UnitCompare(startline.version, "HTTP/1.1");

	if (headers.headers.size() != headerSucsess.size()) {
		std::cerr << "no size\n";
	}
	for (int i = 0; i < 13; i++) {
		UnitCompare(headers.headers[i], headerSucsess[i]);
	}

	for (int i = 0; i < bodyes.bodyes.size(); i++) {
		if (bodyes.bodyes[i] != "")
			std::cerr << "no bodyes = " << bodyes.bodyes[i];
	}
}