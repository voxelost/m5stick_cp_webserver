
#ifndef ENDPOINTS_H
#define ENDPOINTS_H

#include "HTTP/HTTPServer.h"
#include "HTTP/HTTPRequest.h"
#include "JSON/JSONReader.h"
#include "M5StickCPlus.h"

#define endpoint_t(name) String (name)(const HTTPRequest& request)

endpoint_t(echo) {
    return request.body.body;
}

endpoint_t(gyro_data) {
    char* buf = (char*)calloc(3 * 8 + 1, sizeof(char));

    float axis[3];
    m5.Imu.Init();
    m5.Imu.getGyroData(axis, axis + 1, axis + 2);

    sprintf(buf, "%3.3f %3.3f %3.3f", axis[0], axis[1], axis[2]);
    String out(buf);
    free(buf);
    return out;
}

endpoint_t(temp) {
    char* buf = (char*)calloc(9, sizeof(char));

    float temp;
    m5.Imu.Init();
    m5.Imu.getTempData(&temp);

    sprintf(buf, "%3.3f", temp);
    String out(buf);
    free(buf);
    return out;
}

endpoint_t(json) {
    JSONReader json_reader;
    json_reader.parse_obj(request.body.body);


    return "in progress...";
}

#endif
