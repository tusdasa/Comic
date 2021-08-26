//
// Created by Administrator on 8/19/2021.
//

#ifndef COMIC_UTILS_H
#define COMIC_UTILS_H

#include <string>
#include <iostream>
#include <android/log.h>
#include <lua-5.4.3/lua.hpp>
#include <lua-5.4.3/lua.h>
#include <lua-5.4.3/lualib.h>
#include <lua-5.4.3/lauxlib.h>
#include <malloc.h>
#include <curl/curl.h>
#include <ctime>


//const char * clinet ="-----BEGINCERTIFICATE-----MIIFhzCCBG+gAwIBAgIQAf0iJaSTOqMViXaZk8LfIzANBgkqhkiG9w0BAQsFADBuMQswCQYDVQQGEwJVUzEVMBMGA1UEChMMRGlnaUNlcnQgSW5jMRkwFwYDVQQLExB3d3cuZGlnaWNlcnQuY29tMS0wKwYDVQQDEyRFbmNyeXB0aW9uIEV2ZXJ5d2hlcmUgRFYgVExTIENBIC0gRzEwHhcNMjEwMjAzMDAwMDAwWhcNMjIwMjAzMjM1OTU5WjAaMRgwFgYDVQQDEw93d3cudHVzZGFzYS5uZXQwggEiMA0GCSqGSIb3DQEBAQUAA4IBDwAwggEKAoIBAQDYtzeDFXvW1DIimSzuG+4xuefQBKJVYSKi+q0x24Rf37krqRxZzAGU5nDmFr/tB8cHyEfBm8vRAyUqPNOcJ9ai12uD5afqclkdrxDQYrmxz4nLQpN0nyW2H20NF6cJk5FzoJJgZws1fHsAGjta96BuLG+S0UhZouga/jyxPdkRq6Zu2MHtrm/ffjIUvbMn1Yu2VJdE5IsbJ4PvtMK8TBfjx0dTMZCMhVOZIDhZB0Z7n9D9CeTAslAkpgboLmpATv/97OwS4gge5r2CetzOVt5KBrsxJNl4FzTa75RJwA3X5eLl435QrvwDK2d4W3l2oAFPR1+Mlu01uXhPU8GSjtSlAgMBAAGjggJzMIICbzAfBgNVHSMEGDAWgBRVdE+yck/1YLpQ0dfmUVyaAYca1zAdBgNVHQ4EFgQUDfYCEONYQZL4t95tErQ8Utgo2uwwJwYDVR0RBCAwHoIPd3d3LnR1c2Rhc2EubmV0ggt0dXNkYXNhLm5ldDAOBgNVHQ8BAf8EBAMCBaAwHQYDVR0lBBYwFAYIKwYBBQUHAwEGCCsGAQUFBwMCMD4GA1UdIAQ3MDUwMwYGZ4EMAQIBMCkwJwYIKwYBBQUHAgEWG2h0dHA6Ly93d3cuZGlnaWNlcnQuY29tL0NQUzCBgAYIKwYBBQUHAQEEdDByMCQGCCsGAQUFBzABhhhodHRwOi8vb2NzcC5kaWdpY2VydC5jb20wSgYIKwYBBQUHMAKGPmh0dHA6Ly9jYWNlcnRzLmRpZ2ljZXJ0LmNvbS9FbmNyeXB0aW9uRXZlcnl3aGVyZURWVExTQ0EtRzEuY3J0MAkGA1UdEwQCMAAwggEFBgorBgEEAdZ5AgQCBIH2BIHzAPEAdgApeb7wnjk5IfBWc59jpXflvld9nGAK+PlNXSZcJV3HhAAAAXdnF4FiAAAEAwBHMEUCIQCQmA+T9LYiq6uBRKQpW1fT4ZWti2oPXzhAtzSdMHWesgIgRD0xfne0NK54R+ga3ES2an2K1jqSMgtz2B1bb1qqdJ0AdwAiRUUHWVUkVpY/oS/x922G4CMmY63AS39dxoNcbuIPAgAAAXdnF4GkAAAEAwBIMEYCIQDtUeZY8V/q07ix/okDLlVsbLgxNKOfMlnTXIkDjj0dQwIhAKQLgrkjAKh37mdbQ5BWuh79/YSSTYuKdM+hJ8ES6YZuMA0GCSqGSIb3DQEBCwUAA4IBAQBlCuFIIntO8TY92ti7PLqxjYrpIPi1TqFBuaiYAdX/bBsO1A5/C62HrDCzhTCt8vJTJ20vY2ZhyHUR84o30Kkjhk1Io8iRI57lv0o1QmUV9BAqbNKmnA2XcFFkcpDv1CC9hU/JCcl5EFVr2xQJPxnZyIJQxyZlSqDzxbWiVZNn/r6U6qOmL434rz27FsFQhb31pax5s41HehA5jn/q4ooFKuy1xZy8u1wYZPXxpWd2AhXSuDjJXWVX6wtT4TTTNgfd5TRMkbvv9lowcsM4Xelew8ycHwNXE5Yt8MZNu/wXPFG3u1xEEnso79Rp5I46Av45dIdC9JRiCyEGD9cLFvkQ-----ENDCERTIFICATE-----";

//const char * key = "-----BEGINRSAPRIVATEKEY-----MIIEpAIBAAKCAQEA2Lc3gxV71tQyIpks7hvuMbnn0ASiVWEiovqtMduEX9+5K6kcWcwBlOZw5ha/7QfHB8hHwZvL0QMlKjzTnCfWotdrg+Wn6nJZHa8Q0GK5sc+Jy0KTdJ8lth9tDRenCZORc6CSYGcLNXx7ABo7WvegbixvktFIWaLoGv48sT3ZEaumbtjB7a5v334yFL2zJ9WLtlSXROSLGyeD77TCvEwX48dHUzGQjIVTmSA4WQdGe5/Q/QnkwLJQJKYG6C5qQE7//ezsEuIIHua9gnrczlbeSga7MSTZeBc02u+UScAN1+Xi5eN+UK78AytneFt5dqABT0dfjJbtNbl4T1PBko7UpQIDAQABAoIBADGr+uYJbk9M5ynddHol/jg5DVw1N7T8lNkIvlpDX4mvCGzsr7IYS5OCpwVh2P897V1IB0Rlznc7cpEGDJWJ3w0HdZ3vbUeUCn9+gQrWWgwajtF/ErekA5uFA/SAg5lzEJ9RQkOk0qGhhLq/CHQ+9i9ScYdT/zKGX49STvxr+d0tz6if5rKJdrl90EJiTiCHv3sfpAUsY90KUusF0afcvT95/5luHxu2WFOWhzNtpDJRvYBFt4Gavo++6agXYYPco/6+9HJ/RcU3Xpm7okOjpPZTOXDV9NzdVWu5xxuQ2FPQa6vOLdQLlkvnONuJVfWOzahnWG1AhAH2TSlsgnkxRdkCgYEA/hrecYNmFk+2bwsOB5yQ6LoGL2dppnjY5oWIBlsC5CoWT6q7vMKWkdDa/29M+aUZCCMULXGqMl4a+wKFhmuXHEVTBNcbu9YDcMI0Z3kITJsRJqR+T9VK/BzxHAjDctPFrmbj6t+IHXNIEjBsGmG8G/8DF+7KxdoAg4jYITyOvr0CgYEA2lT3GbJqpuju8U8mgv1ohP4v+U4RmXkxbRA+7ynlML0+pRaW7Fh8UezCy5PSxWXAwOaeY8GsKAJ/yqMPqKjPU1AuuDOCbhsVbvqvOi/PhzLTr8p2FRXNNaKZWuNTe0sCjAxWu799Plu2Rtq2+ThipD70qgs4UF8auzOr42LkoAkCgYEApGOBkPIu8zQyk/gU5Xu2i7j9E2HViasYt1mfvGzYm/9WW8famK1Sd5ckdqfspnzWitsWzKeCMf+LeOQSufmU0udOZA09lfFIXIRnHqHAar7PA67bQI5+akfW/An3V6wFcWSDAooGJvdTouDMruyXo40A1VTYvdLhDjdTi3z/5AkCgYEAkQHTZ/7GtPqKED0Yf/FcZNAJ/tOp/ruuZxheJCw4K2nVXIInVOvkDelo6xrP5wkQv02sLucntx8JzwUD1mnf4R6lGPQlEYntb1sR3Fx6wfmw/NVEHfbv50qJ/gJzpLSKCYf8Zw/kV/FDm8WRtu6LHTku+G0hRsgTkffcltZMsDkCgYBuQ7xb/bnAz0TqdS1G1OohMLvQHwqgP+UZLtC/X2J5OBYgseECBncvRwlJPiJbPW+/HZ1XyRxhHHxXUd5oDUwAhP6uKVfYQsDVCwuzbn4Px6g2XGkBhtPtL6H2Mo4ca77TwIUaUByLZjrLuwjIxVAkbjEL0ftH8odPmh+96BVkkw==-----ENDRSAPRIVATEKEY-----";



struct MemoryStruct {
    char *memory;
    size_t size;
};


static size_t
WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp);
/**
 *
 * @param str1
 * @return
 */
std::string
sha(const std::string& source);

std::string
runLua(const std::string& source);

std::string
CurlRequest(const std::string& url,
            const std::string& apiKey,
            const std::string& uuid,
            const std::string& appChannel);


#endif //COMIC_UTILS_H