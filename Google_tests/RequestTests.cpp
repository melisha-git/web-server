#include "gtest/gtest.h"
#include "../IHTTPMessage.interface/Request.class/Request.hpp"


TEST(Request, StartlineGetTestMethod) {
	Request request("GET / HTTP/1.1");

	EXPECT_EQ(request.getStartLine().method, "GET");
}

TEST(Request, StartlinePostTestMethod) {
	Request request("POST / HTTP/1.1");

	EXPECT_EQ(request.getStartLine().method, "POST");
}

TEST(Request, StartlineDeleteTestMethod) {
	Request request("DELETE / HTTP/1.1");

	EXPECT_EQ(request.getStartLine().method, "DELETE");
}

TEST(Request, StartlineJustTestTarget) {
	Request request("GET / HTTP/1.1");

	EXPECT_EQ(request.getStartLine().target, "/");
}

TEST(Request, StartlineIndexTestTarget) {
	Request request("GET /index.html HTTP/1.1");

	EXPECT_EQ(request.getStartLine().target, "/index.html");
}

TEST(Request, StartlineFaviconTestTarget) {
	Request request("GET /favicon.ico HTTP/1.1");

	EXPECT_EQ(request.getStartLine().target, "/favicon.ico");
}

TEST(Request, StartlineTestVersion) {
	Request request("GET /favicon.ico HTTP/1.1");

	EXPECT_EQ(request.getStartLine().version, "HTTP/1.1");
}

TEST(Request, HeadersTestNN) {
	Request request("GET /favicon.ico HTTP/1.1\n"
					"Host: developer.mozilla.org\n"
					"Accept-Language: fr\n\n");
	std::vector<std::string> vc = {"Host: developer.mozilla.org", "Accept-Language: fr"};
	EXPECT_EQ(request.getHeaders().headers, vc);
}

TEST(Request, HeadersTestNoBodyes) {
	Request request("GET /favicon.ico HTTP/1.1\n"
					"Host: developer.mozilla.org\n"
					"Accept-Language: fr");
	std::vector<std::string> vc = {"Host: developer.mozilla.org", "Accept-Language: fr"};
	EXPECT_EQ(request.getHeaders().headers, vc);
}

TEST(Request, HeadersTestBodyes) {
	Request request("GET /favicon.ico HTTP/1.1\n"
					"Host: developer.mozilla.org\n"
					"Accept-Language: fr\n\n"
					"FUCKING BITCH\n"
					"SOSI KIRPICH\n");
	std::vector<std::string> vc = {"Host: developer.mozilla.org", "Accept-Language: fr"};
	EXPECT_EQ(request.getHeaders().headers, vc);
}

TEST(Request, BodyesTestNoBodyes) {
	Request request("GET /favicon.ico HTTP/1.1\n"
					"Host: developer.mozilla.org\n"
					"Accept-Language: fr\n\n");
	std::vector<std::string> vc;
	EXPECT_EQ(request.getBodyes().bodyes, vc);
}

TEST(Request, BodyesTestBodyes) {
	Request request("GET /favicon.ico HTTP/1.1\n"
					"Host: developer.mozilla.org\n"
					"Accept-Language: fr\n\n"
					"FUCKING BITCH\n"
					"SOSI KIRPICH");
	std::vector<std::string> vc = {"FUCKING BITCH\n"
								   "SOSI KIRPICH"};
	EXPECT_EQ(request.getBodyes().bodyes, vc);
}