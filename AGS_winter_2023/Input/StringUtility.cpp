#include "StringUtility.h"
#include<DxLib.h>
#include<cassert>
std::wstring StringUtility::StringToWstring(const std::string& str)
{

    std::wstring ret;
    auto result = MultiByteToWideChar(
                                    CP_UTF8,
                                    0,
                                    str.c_str(),//入力文字列
                                    str.length(),
                                    nullptr,//文字数が確定してないから,nullptr
                                    0);

    assert(result >= 0);
    ret.resize(result);//確保する
    //二度目の呼び出しは変換
    result = MultiByteToWideChar(
        CP_UTF8,
        0,
        str.c_str(),//入力文字列
        str.length(),
         ret.data(),//文字数が確定してないから,nullptr
        ret.size());

    return ret;
}

std::string StringUtility::WstringToString(const std::wstring& wstr)
{
    std::string ret;
    //一度目の呼び出しは文字数を知るため
    auto result = WideCharToMultiByte(
        CP_ACP,
        0,
        wstr.c_str(),//入力文字列
        wstr.length(),
        nullptr,//文字数が確定してないから,nullptr
        0,
        nullptr,
        nullptr);

    assert(result >= 0);
    ret.resize(result);//確保する

    //二度目の呼び出しは変換
    result = WideCharToMultiByte(
        CP_ACP,
        0,
        wstr.c_str(),//入力文字列
        wstr.length(),
        ret.data(),//文字数が確定してないから,nullptr
        ret.size(),
        nullptr,
        nullptr);

    return ret;
}
