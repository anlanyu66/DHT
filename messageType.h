//
// Created by Anlan Yu on 2/5/20.
//

#ifndef DHT_MESSAGETYPE_H
#define DHT_MESSAGETYPE_H
#define BUFFER 400
enum OperationType {
    PUT = 1,
    GET,
};

template <typename T>
struct RequestInfo {
    long operation_type;
    int hash_key;
    T hash_value;
};

template <typename T>
struct ResponseInfo {
    long operation_type;
    int hash_key;
    int status;
    T hash_value;
};
#endif //DHT_MESSAGETYPE_H
