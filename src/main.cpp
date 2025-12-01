#include <windows.h>
#include <winhttp.h>
#include <iostream>
#include <string>
#include <nlohman/json.hpp>

#pragma comment(lib, "winhttp.lib")

using json = nlohmann::json;
using namespace std;

string httpGet(const wstring &domain, const wstring &path)
{
    HINTERNET hSession = WinHttpOpen(L"WinHTTP Get Client/1.0",
                                     WINHTTP_ACCESS_TYPE_DEFAULT_PROXY,
                                     WINHTTP_NO_PROXY_NAME,
                                     WINHTTP_NO_PROXY_BYPASS, 0);

    if (!hSession)
        return "Failed to open session";

    HINTERNET hConnect = WinHttpConnect(hSession, domain.c_str(), INTERNET_DEFAULT_HTTPS_PORT, 0);
    if (!hConnect)
        return "Failed to connect";

    HINTERNET hRequest = WinHttpOpenRequest(
        hConnect, L"GET", path.c_str(),
        NULL, WINHTTP_NO_REFERER,
        WINHTTP_DEFAULT_ACCEPT_TYPES,
        WINHTTP_FLAG_SECURE);

    if (!hRequest)
        return "Failed to open request";

    BOOL sent = WinHttpSendRequest(hRequest,
                                   WINHTTP_NO_ADDITIONAL_HEADERS,
                                   0,
                                   WINHTTP_NO_REQUEST_DATA,
                                   0,
                                   0,
                                   0);

    if (!sent)
        return "Failed to send";

    WinHttpReceiveResponse(hRequest, NULL);

    DWORD dwSize = 0;
    string response;

    do
    {
        WinHttpQueryDataAvailable(hRequest, &dwSize);
        if (dwSize == 0)
            break;

        char *buffer = new char[dwSize + 1];
        ZeroMemory(buffer, dwSize + 1);

        DWORD bytesRead = 0;
        WinHttpReadData(hRequest, buffer, dwSize, &bytesRead);

        response.append(buffer, bytesRead);
        delete[] buffer;

    } while (dwSize > 0);

    WinHttpCloseHandle(hRequest);
    WinHttpCloseHandle(hConnect);
    WinHttpCloseHandle(hSession);

    return response;
}

int main()
{

    string resp = httpGet(
        L"api.open-meteo.com",
        L"/v1/forecast?latitude=-7.25&longitude=112.75&current_weather=true");

    cout << "RAW RESPONSE:\n"
         << resp << "\n\n";

    try
    {
        auto jsonResp = json::parse(resp);

        cout << "CUACA SAAT INI (Surabaya):\n";
        cout << "Temperature : " << jsonResp["current_weather"]["temperature"] << "°C\n";
        cout << "Wind Speed  : " << jsonResp["current_weather"]["windspeed"] << " km/h\n";
        cout << "Time        : " << jsonResp["current_weather"]["time"] << "\n";
    }
    catch (...)
    {
        cout << "Failed to parse JSON.\n";
    }

    return 0;
}
