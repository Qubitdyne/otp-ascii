# Name: otp-base64-gen, Version: 1.1
# Description: One-time Pad Base64 Manifold Generator.
# Author: Nikolas J. Britton
# Copyright © 2023 Qubitdyne, Inc. All Rights Reserved.

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <array>
#include <algorithm>
#include <random>
#include <cstdio>
#include <unistd.h>

using namespace std;

array<int, 32> index = {43, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 97, 98, 99, 100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116, 117, 118, 119, 120, 121, 122};
array<int, 32> index_shuf;

string key_gen(){
    string result = "";
    for(int i = 0; i < 20; i++){
        string str = "KEY";
        str += to_string(i);
        str += " ";
        for(int j = 0; j < 64; j++){
            char c;
            c = (rand() % (90-65+1)) + 65;
            if(c >= 65 && c <= 90){
                str += c;
            }
            else{
                c = (rand() % (122-97+1)) + 97;
                str += c;
            }
        }
        result += str;
    }
    return result;
}

bool check_array(int item){
    for(int i = 0; i < index_shuf.size(); i++){
        if(index_shuf[i] == item){
            return 0;
        }
    }
    return 1;
}

void index_shuf(){
    while(index_shuf.size() != index.size()){
        int rand = rand() % index.size();
        if(check_array(index[rand])){
            index_shuf[index_shuf.size()] = index[rand];
        }
    }
}

string index_ab(){
    string result = "";
    for(int i = 0; i < index.size()-20; i++){
        char arr[4];
        sprintf(arr, "\\%03o", index[i]);
        result += arr;
    }
    return result;
}

string index_cd(){
    string result = "";
    for(int i = index.size()-1; i >= index.size()-20; i--){
        char arr[4];
        sprintf(arr, "\\%03o", index[i]);
        result += arr;
    }
    return result;
}

string index_ac(){
    string result = "";
    for(int i = 0; i < index.size()-20; i++){
        char arr[4];
        sprintf(arr, "\\%03o\n", index[i]);
        result += arr;
    }
    return result;
}

string index_bd(){
    string result = "";
    for(int i = index.size()-1; i >= index.size()-20; i--){
        char arr[4];
        sprintf(arr, "\\%03o\n", index[i]);
        result += arr;
    }
    return result;
}

string index_ki(){
    index_shuf();
    string result = "";
    for(int i = 0; i < index_shuf.size(); i++){
        char arr[4];
        sprintf(arr, "\\%03o", index_shuf[i]);
        result += arr;
    }
    index_shuf.fill(0);
    return result;
}

string index_kj(){
    index_shuf();
    string result = "";
    for(int i = 0; i < index_shuf.size(); i++){
        char arr[4];
        sprintf(arr, "\\%03o\n", index_shuf[i]);
        result += arr;
    }
    index_shuf.fill(0);
    return result;
}

string index_horizontal(){
    string result = index_ab() + "\n" + index_ki() + "\n" + index_cd() + "\n";
    return result;
}

string index_vertical(){
    string result = index_ac() + index_kj() + index_bd() + "\n";
    for(int i = 0; i < 64; i++){
        char arr[3];
        sprintf(arr, "%02d", i);
        result += arr;
        result += " ";
    }
    return result;
}

string index_key(){
    string result = "a#b##\n#kilm\ncjdnn\n";
    return result;
}

string otp_graph(){
    string result = "";
    for(int i = 0; i < 64; i++){
        char c;
        c = (rand() % (90-65+1)) + 65;
        if(c >= 65 && c <= 90){
            result += c;
        }
        else{
            c = (rand() % (122-97+1)) + 97;
            result += c;
        }
    }
    return result;
}

string otp_ascii(){
    string result = index_key() + index_horizontal() + index_vertical() + otp_graph() + "\n";
    return result;
}

string sha_512256(string str1, string str2){
    string result = "";
    FILE *fp;
    char path[1035];
    string command = "egrep " + str1 + " " + str2 + " " + to_string(time(NULL)) + ".otp | shasum -a 512256";
    fp = popen(command.c_str(), "r");
    if(fp == NULL){
        cout << "Failed to run command\n";
        exit(1);
    }
    while(fgets(path, sizeof(path)-1, fp) != NULL){
        result += path;
    }
    pclose(fp);
    return result;
}

int main(int argc, char* argv[]){
    srand(time(NULL));
    string timestamp = to_string(time(NULL));

    FILE *fp;
    fp = fopen((timestamp + ".otp").c_str(), "w");
    if(fp == NULL){
        cout << "Unable to create " << getcwd(NULL, 0) << "/" << timestamp << ".otp, exiting.\n";
        return 1;
    }

    string key_gen_result = key_gen();
    fputs(key_gen_result.c_str(), fp);

    string otp_ascii_result = otp_ascii();
    fputs(otp_ascii_result.c_str(), fp);

    string sha_512256_result = sha_512256("-a", "^KEY[0-1][0-9]");
    string sha_512256_result2 = sha_512256("-av", "^KEY[0-1][0-9]|^SHA0[0-3]");
    string sha_512256_result3 = sha_512256("-a", ".*");

    fputs(("SHA01 " + sha_512256_result).c_str(), fp);
    fputs(("SHA02 " + sha_512256_result2).c_str(), fp);
    fputs(("SHA03 " + sha_512256_result3).c_str(), fp);
    fclose(fp);

    string command2 = "shasum -a 512256 " + timestamp + ".otp";
    FILE *fp2;
    char path2[1035];
    fp2 = popen(command2.c_str(), "r");
    if(fp2 == NULL){
        cout << "Failed to run command\n";
        exit(1);
    }
    while(fgets(path2, sizeof(path2)-1, fp2) != NULL){
        string sha_512256_result4 = path2;
        sha_512256_result4.erase(sha_512256_result4.size()-1);
        fputs(("SHA04 " + sha_512256_result4 + "\n").c_str(), fp);
    }
    pclose(fp2);

    if(string(argv[1]) != "-s"){
        fp = fopen((timestamp + ".otp").c_str(), "r");
        char path[1035];
        while(fgets(path, sizeof(path)-1, fp) != NULL){
            printf("%s", path);
        }
        cout << timestamp;
    }

    return 0;
}
