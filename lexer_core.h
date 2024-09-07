#define PROTO_CODE(false)

#ifdef USING(PROTO_CODE)

// /*

#pragma once
//#include <iostream>

#include <cstdint>

#include <string>
#include <string_view>
#include <format>

#include <chrono>


/*
* 
*   DEBUG CONDITIONS
#if USING(DEBUG)
        <...>
#endif
// */

#define DBG true // <-- SET DEBUG MACRO

// buffer sizes MACRO TABLES
#define _LIM_BUF 64
#define _MID_BUF 32
#define _LOW_BUF 8

template <typename T>
class DBG_SET;
class SymbolicPrimitives;

#include <vector>
#include <tuple>
#include <unordered_map>
#include <array>

using namespace std;

class LexerCore :
    SymbolicPrimitives
{
    LexerCore();
    ~LexerCore();
public:
    //DEBUG SET
private:

protected:
    
};

class SymbolicPrimitives {
protected:
    enum primitive_sets {
        LHS, RHS, 
        FX, CONSTRUCT,
        _WSP, _TAB, _NL
    };
    template <typename V, typename S>
    struct primitive_syntax {
        /*LEFT-FX & RIGHT-FX*/ V LHS, RHS;
        /*SUM OR RESULTAT*/    S _RES, _SUM, _OP;
        /*FUNCTION & STRUCTURE*/  V FX, CONSTRUCT;
        /* SYNTAX OPS*/  V _eq, _sum, _
    };

};

LexerCore::LexerCore() 
{

};
LexerCore::~LexerCore() 
{
    
};

template <typename T>
class DBG_SET {

};

 */
#endif