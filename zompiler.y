%{
#include "node.h"
#include <iostream>
#include <string>
extern int yylex();
extern void yyerror(const char* s);

// Global for the main block
NBlock* g_MainBlock = nullptr;

// Disable the warnings that Bison creates
#pragma warning(disable: 4065)
%}

/* Add one union member for each Node* type */
%union {
    Node* node;
	NBlock* block;
	NStatement* statement;
	NNumeric* numeric;
	NBoolean* boolean;
	std::string* string;
	int token;
}

%error-verbose

/* Terminal symbols */
%token <string> TINTEGER
%token <token> TLBRACE TRBRACE TSEMI TLPAREN TRPAREN
%token <token> TMAIN TROTATE TFORWARD TISHUMAN TATTACK TISPASSABLE TISRANDOM TISZOMBIE TRANGEDATTACK
%token <token> TIF TELSE

/* Statements */
%type <block> main_loop block
%type <statement> statement rotate forward ifelse attack rangedattack
%type <boolean> boolean ishuman ispassable israndom iszombie
 
/* Expressions */
%type <numeric> numeric

%%

main_loop	: TMAIN TLBRACE block TRBRACE { std::cout << "Main entry point found!" << std::endl;
    g_MainBlock = $3;
    $3->SetMainBlock();}
;

block		: statement { std::cout << "Single statement" << std::endl;
                $$ = new NBlock();
                $$->AddStatement($1);}
            | block statement { std::cout << "Multiple statements" << std::endl;
                $$->AddStatement($2);}
;

boolean     : ishuman
            | ispassable
            | israndom
            | iszombie
;

statement	: rotate TSEMI
            | forward TSEMI
            | ifelse
            | attack TSEMI
            | rangedattack TSEMI
;

ifelse      : TIF TLPAREN boolean TRPAREN TLBRACE block TRBRACE TELSE TLBRACE block TRBRACE { std::cout << "If else statement" << std::endl;
                $$ = new NIfElse($3, $6, $10);}
;

rotate		: TROTATE TLPAREN numeric TRPAREN { std::cout << "Rotate command" << std::endl;
                $$ = new NRotate($3);}
;

forward     : TFORWARD TLPAREN TRPAREN { std::cout << "Forward command" <<
    std::endl;
                $$ = new NForward();}
;

ishuman     : TISHUMAN TLPAREN numeric TRPAREN { std::cout << "Is human command" << std::endl;
                $$ = new NIsHuman($3);}
;

iszombie     : TISZOMBIE TLPAREN numeric TRPAREN { std::cout << "Is zombie command" << std::endl;
                $$ = new NIsZombie($3);}
;

ispassable  : TISPASSABLE TLPAREN TRPAREN { std::cout << "Is passable command" << std::endl;
                $$ = new NIsPassable();}
;

israndom    : TISRANDOM TLPAREN TRPAREN { std::cout << "Is random command" << std::endl;
                $$ = new NIsRandom();}
;

attack      : TATTACK TLPAREN TRPAREN { std::cout << "Attack command" << std::endl;
                $$ = new NAttack();}
;

rangedattack      : TRANGEDATTACK TLPAREN TRPAREN { std::cout << "Ranged attack command" << std::endl;
                    $$ = new NRangedAttack();}
;

numeric		: TINTEGER { std::cout << "Numeric value of " << *($1) << std::endl;
                $$ = new NNumeric(*($1));}
;

%%
