/*
 * Helper.cpp
 *
 *  Created on: Nov 28, 2023
 *      Author: cyberreefguru
 */
#include "Helper.h"

const char* Helper::toString(WiFiEvent_t w)
{
    switch (w) {
        case ARDUINO_EVENT_WIFI_READY: 
            return "READY";
            break;
        case ARDUINO_EVENT_WIFI_SCAN_DONE:
            return "SCAN COMPLETE";
            break;
        case ARDUINO_EVENT_WIFI_STA_START:
            return "STA START";
            break;
        case ARDUINO_EVENT_WIFI_STA_STOP:
            return "STA STOP";
            break;
        case ARDUINO_EVENT_WIFI_STA_CONNECTED:
            return "STA CONNECTED";
            break;
        case ARDUINO_EVENT_WIFI_STA_DISCONNECTED:
            return "STA DISCONNECTED";
            break;
        case ARDUINO_EVENT_WIFI_STA_AUTHMODE_CHANGE:
            return "STA AUTHMODE CHANGE";
            break;
        case ARDUINO_EVENT_WIFI_STA_GOT_IP:
            return "STA GOT IP";
            break;
        case ARDUINO_EVENT_WIFI_STA_GOT_IP6:
            return "STA GOT IP6";
            break;
        case ARDUINO_EVENT_WIFI_STA_LOST_IP:
            return "STA LOST IP";
            break;
        case ARDUINO_EVENT_WIFI_AP_START:
            return "AP START";
            break;
        case ARDUINO_EVENT_WIFI_AP_STOP:
            return "AP STOP";
            break;
        case ARDUINO_EVENT_WIFI_AP_STACONNECTED:
            return "AP STA CONNECTED";
            break;
        case ARDUINO_EVENT_WIFI_AP_STADISCONNECTED:
            return "AP STA DISCONNECTED";
            break;
        case ARDUINO_EVENT_WIFI_AP_STAIPASSIGNED:
            return "AP STA IP ASSIGNED";
            break;
        case ARDUINO_EVENT_WIFI_AP_PROBEREQRECVED:
            return "AP PROBE REQUEST";
            break;
        case ARDUINO_EVENT_WIFI_AP_GOT_IP6:
            return "AP GOT IP6";
            break;
        case ARDUINO_EVENT_WIFI_FTM_REPORT:
            return "FTM REPORT";
            break;
        case ARDUINO_EVENT_ETH_START:
            return "ETH START";
            break;
        case ARDUINO_EVENT_ETH_STOP:
            return "ETH STOP";
            break;
        case ARDUINO_EVENT_ETH_CONNECTED:
            return "ETH CONNECTED";
            break;
        case ARDUINO_EVENT_ETH_DISCONNECTED:
            return "ETH DISCONNECTED";
            break;
        case ARDUINO_EVENT_ETH_GOT_IP:
            return "ETH GOT IP";
            break;
        case ARDUINO_EVENT_ETH_GOT_IP6:
            return "ETH GOT IP6";
            break;
        case ARDUINO_EVENT_WPS_ER_SUCCESS:
            return "WPS ER SUCCESS";
            break;
        case ARDUINO_EVENT_WPS_ER_FAILED:
            return "WPS ER FAIL";
            break;
        case ARDUINO_EVENT_WPS_ER_TIMEOUT:
            return "WPS ER TIMEOUT";
            break;
        case ARDUINO_EVENT_WPS_ER_PIN:
            return "WPS ER PIN";
            break;
        case ARDUINO_EVENT_WPS_ER_PBC_OVERLAP:
            return "WPS ER PCB OVERLAP";
            break;
        case ARDUINO_EVENT_SC_SCAN_DONE:
            return "SC SCAN DONE";
            break;
        case ARDUINO_EVENT_SC_FOUND_CHANNEL:
            return "SC FOUND CHANNEL";
            break;
        case ARDUINO_EVENT_SC_GOT_SSID_PSWD:
            return "SC GOT SSID PSWD";
            break;
        case ARDUINO_EVENT_SC_SEND_ACK_DONE:
            return "SC SEND ACK DONE";
            break;
        case ARDUINO_EVENT_PROV_INIT:
            return "PROV INIT";
            break;
        case ARDUINO_EVENT_PROV_DEINIT:
            return "PROV DEINIT";
            break;
        case ARDUINO_EVENT_PROV_START:
            return "PROV START";
            break;
        case ARDUINO_EVENT_PROV_END:
            return "PROV END";
            break;
        case ARDUINO_EVENT_PROV_CRED_RECV:
            return "PROV CRED RECV";
            break;
        case ARDUINO_EVENT_PROV_CRED_FAIL:
            return "PROV CRED FAIL";
            break;
        case ARDUINO_EVENT_PROV_CRED_SUCCESS:
            return "PROV CRED SUCCESS";
            break;
        default: 
            return "UNKNOWN";
        break;
    }
}


const char* Helper::toString(State val)
{
    switch (val)
    {
    case State::ACTIVE:
        return "ACTIVE";
        break;
    case State::DEACTIVE:
        return "DEACTIVE";
        break;
    case State::ERROR:
        return "ERROR";
        break;
    case State::INITIALIZING:
        return "INITIALIZING";
        break;
    case State::MQTT_DOWN:
        return "MQTT_DOWN";
        break;
    case State::MQTT_UP:
        return "MQTT_UP";
        break;
    case State::PROCESSING:
        return "PROCESSING";
        break;
    case State::RECEIVED:
        return "RECEIVED";
        break;
    case State::RECEIVING:
        return "RECEIVING";
        break;
    case State::SENDING:
        return "SENDING";
        break;
    case State::SENT:
        return "SENT";
        break;
    case State::WAITING:
        return "WAITING";
        break;
    case State::WIFI_DOWN:
        return "WIFI_DOWN";
        break;
    case State::WIFI_UP:
        return "WIFI_UP";
        break;
    default:
        return "UNKNOWN";
        break;
    }
}
