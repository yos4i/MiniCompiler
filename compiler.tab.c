/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "compiler.y"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"
#include "semantic.h"
#include "3ac_generator.h"

node* ast_root = NULL;
int syntax_error_occurred = 0; 
int yylex(void);
void yyerror(const char *msg);
void printtree(node *tree, int level);
int syntax_error_count = 0;
node* append_node(node* list, node* new_node);
char* current_function = NULL;
char currentLineText[1024] = "";
int currentPos = 0;
int param_count = 0;
int func_counter = 1;

char* generate_expr_code(node* expr);
void generate_stmt_code(node* stmt);
void generate_func_code(node* func);


#line 98 "compiler.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "compiler.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_BOOL_LIT = 3,                   /* BOOL_LIT  */
  YYSYMBOL_REL_OP = 4,                     /* REL_OP  */
  YYSYMBOL_DEF = 5,                        /* DEF  */
  YYSYMBOL_TOKEN_TYPE = 6,                 /* TOKEN_TYPE  */
  YYSYMBOL_POW = 7,                        /* POW  */
  YYSYMBOL_INT_LIT = 8,                    /* INT_LIT  */
  YYSYMBOL_HEX_LIT = 9,                    /* HEX_LIT  */
  YYSYMBOL_FLOAT_LIT = 10,                 /* FLOAT_LIT  */
  YYSYMBOL_STRING_LIT = 11,                /* STRING_LIT  */
  YYSYMBOL_ID = 12,                        /* ID  */
  YYSYMBOL_MAIN_ID = 13,                   /* MAIN_ID  */
  YYSYMBOL_IF = 14,                        /* IF  */
  YYSYMBOL_ELIF = 15,                      /* ELIF  */
  YYSYMBOL_ELSE = 16,                      /* ELSE  */
  YYSYMBOL_WHILE = 17,                     /* WHILE  */
  YYSYMBOL_RETURN = 18,                    /* RETURN  */
  YYSYMBOL_TOKEN_PASS = 19,                /* TOKEN_PASS  */
  YYSYMBOL_AND = 20,                       /* AND  */
  YYSYMBOL_OR = 21,                        /* OR  */
  YYSYMBOL_NOT = 22,                       /* NOT  */
  YYSYMBOL_IS = 23,                        /* IS  */
  YYSYMBOL_ARROW = 24,                     /* ARROW  */
  YYSYMBOL_PRINT = 25,                     /* PRINT  */
  YYSYMBOL_26_ = 26,                       /* '='  */
  YYSYMBOL_27_ = 27,                       /* '+'  */
  YYSYMBOL_28_ = 28,                       /* '-'  */
  YYSYMBOL_29_ = 29,                       /* '*'  */
  YYSYMBOL_30_ = 30,                       /* '/'  */
  YYSYMBOL_UMINUS = 31,                    /* UMINUS  */
  YYSYMBOL_32_ = 32,                       /* '['  */
  YYSYMBOL_33_ = 33,                       /* ']'  */
  YYSYMBOL_34_ = 34,                       /* '('  */
  YYSYMBOL_35_ = 35,                       /* ')'  */
  YYSYMBOL_36_ = 36,                       /* ':'  */
  YYSYMBOL_37_ = 37,                       /* ';'  */
  YYSYMBOL_38_ = 38,                       /* ','  */
  YYSYMBOL_39_ = 39,                       /* '{'  */
  YYSYMBOL_40_ = 40,                       /* '}'  */
  YYSYMBOL_YYACCEPT = 41,                  /* $accept  */
  YYSYMBOL_CODE = 42,                      /* CODE  */
  YYSYMBOL_FUNC_LIST = 43,                 /* FUNC_LIST  */
  YYSYMBOL_FUNC = 44,                      /* FUNC  */
  YYSYMBOL_ARGS = 45,                      /* ARGS  */
  YYSYMBOL_RET_TYPE = 46,                  /* RET_TYPE  */
  YYSYMBOL_PARAMS = 47,                    /* PARAMS  */
  YYSYMBOL_TYPE_GROUP = 48,                /* TYPE_GROUP  */
  YYSYMBOL_BARE_PARAM_LIST = 49,           /* BARE_PARAM_LIST  */
  YYSYMBOL_DEFAULT_PARAM_LIST = 50,        /* DEFAULT_PARAM_LIST  */
  YYSYMBOL_PARAM_WITH_DEFAULT = 51,        /* PARAM_WITH_DEFAULT  */
  YYSYMBOL_LITERAL = 52,                   /* LITERAL  */
  YYSYMBOL_SUITE = 53,                     /* SUITE  */
  YYSYMBOL_BLOCK = 54,                     /* BLOCK  */
  YYSYMBOL_BODY = 55,                      /* BODY  */
  YYSYMBOL_STMT_LIST = 56,                 /* STMT_LIST  */
  YYSYMBOL_DECLARATION = 57,               /* DECLARATION  */
  YYSYMBOL_DECL_LIST = 58,                 /* DECL_LIST  */
  YYSYMBOL_DECL_ITEM = 59,                 /* DECL_ITEM  */
  YYSYMBOL_STMT = 60,                      /* STMT  */
  YYSYMBOL_PASS = 61,                      /* PASS  */
  YYSYMBOL_PRINT_STMT = 62,                /* PRINT_STMT  */
  YYSYMBOL_LHS = 63,                       /* LHS  */
  YYSYMBOL_LHS_LIST = 64,                  /* LHS_LIST  */
  YYSYMBOL_ASSIGNMENT = 65,                /* ASSIGNMENT  */
  YYSYMBOL_RETURN_STMT = 66,               /* RETURN_STMT  */
  YYSYMBOL_FUNC_CALL = 67,                 /* FUNC_CALL  */
  YYSYMBOL_ARG_LIST = 68,                  /* ARG_LIST  */
  YYSYMBOL_EXPR_LIST = 69,                 /* EXPR_LIST  */
  YYSYMBOL_FUNC_CALL_STMT = 70,            /* FUNC_CALL_STMT  */
  YYSYMBOL_IF_STMT = 71,                   /* IF_STMT  */
  YYSYMBOL_ELIF_LIST = 72,                 /* ELIF_LIST  */
  YYSYMBOL_ELIF_BLOCK = 73,                /* ELIF_BLOCK  */
  YYSYMBOL_WHILE_STMT = 74,                /* WHILE_STMT  */
  YYSYMBOL_EXPR = 75                       /* EXPR  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_uint8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  7
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   470

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  41
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  35
/* YYNRULES -- Number of rules.  */
#define YYNRULES  94
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  170

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   281


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      34,    35,    29,    27,    38,    28,     2,    30,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    36,    37,
       2,    26,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    32,     2,    33,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    39,     2,    40,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    31
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,    57,    57,    62,    63,    65,    68,    72,    73,    75,
      76,    78,    79,    81,    82,    83,    85,    86,    88,    89,
      91,    93,    94,    95,    96,    97,    99,   100,   102,   104,
     105,   107,   108,   110,   112,   113,   115,   116,   119,   120,
     121,   122,   123,   124,   125,   126,   127,   129,   131,   133,
     134,   136,   137,   139,   141,   142,   144,   146,   147,   149,
     150,   152,   155,   156,   157,   158,   161,   162,   165,   167,
     169,   170,   171,   172,   173,   174,   175,   176,   177,   178,
     179,   180,   181,   182,   183,   184,   185,   186,   187,   188,
     189,   190,   191,   192,   193
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "BOOL_LIT", "REL_OP",
  "DEF", "TOKEN_TYPE", "POW", "INT_LIT", "HEX_LIT", "FLOAT_LIT",
  "STRING_LIT", "ID", "MAIN_ID", "IF", "ELIF", "ELSE", "WHILE", "RETURN",
  "TOKEN_PASS", "AND", "OR", "NOT", "IS", "ARROW", "PRINT", "'='", "'+'",
  "'-'", "'*'", "'/'", "UMINUS", "'['", "']'", "'('", "')'", "':'", "';'",
  "','", "'{'", "'}'", "$accept", "CODE", "FUNC_LIST", "FUNC", "ARGS",
  "RET_TYPE", "PARAMS", "TYPE_GROUP", "BARE_PARAM_LIST",
  "DEFAULT_PARAM_LIST", "PARAM_WITH_DEFAULT", "LITERAL", "SUITE", "BLOCK",
  "BODY", "STMT_LIST", "DECLARATION", "DECL_LIST", "DECL_ITEM", "STMT",
  "PASS", "PRINT_STMT", "LHS", "LHS_LIST", "ASSIGNMENT", "RETURN_STMT",
  "FUNC_CALL", "ARG_LIST", "EXPR_LIST", "FUNC_CALL_STMT", "IF_STMT",
  "ELIF_LIST", "ELIF_BLOCK", "WHILE_STMT", "EXPR", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-59)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-31)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      12,    21,    26,    12,   -59,    -6,    -3,   -59,   -59,    37,
      14,    46,    28,    22,   -59,    30,    50,    49,    54,   -59,
      40,    37,   115,    59,    76,    82,    90,    62,   -59,    67,
      94,   -10,   353,   353,     1,    72,    78,     2,   -59,   -59,
     -59,   -59,   -59,   -59,   -59,    -8,   -59,   -59,    73,   -59,
     -59,   -59,   -59,   -59,   -59,   -59,   -59,   -59,    50,    54,
      50,   -59,   -59,   115,   -59,    87,    80,    81,   353,   353,
     -59,   -59,   -59,   -59,   -59,    84,   353,   353,   353,   -59,
     238,   256,   -59,   146,   -59,   353,    85,    83,   -59,   353,
     108,   -59,   -59,   353,   -59,    94,   363,    89,    88,   423,
     325,    96,   292,   353,   353,   353,   353,   353,   353,   353,
     353,   176,   115,   115,   -59,   310,   -59,   -59,   186,    99,
     -59,   423,   -59,   -59,   -59,   353,   -59,    53,     0,   325,
     438,    18,    18,     0,     0,   136,   201,    24,   -59,   100,
     -59,   423,   -59,   353,   378,   -59,   338,   353,    86,    36,
     -59,   -59,   393,   -59,   -59,   220,   274,   115,   102,   -59,
     -59,   -59,   353,   115,   -59,   115,   408,   -59,   -59,   -59
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,     0,     2,     4,     0,     0,     1,     3,     8,
       0,     0,     0,     7,    11,     0,    16,    13,    15,    18,
      10,     0,     0,     0,     0,     0,     0,     0,    12,     0,
       0,    49,     0,     0,     0,     0,     0,     0,     6,    27,
      40,    26,    45,    44,    51,     0,    39,    41,     0,    38,
      42,    43,    25,    21,    22,    23,    24,    20,    17,    14,
       0,    19,     9,     0,    46,    36,     0,    34,     0,    58,
      84,    82,    86,    85,    83,    81,     0,     0,     0,    87,
       0,     0,    55,     0,    47,     0,     0,     0,    32,     0,
       0,    61,     5,     0,    33,     0,     0,     0,    57,    59,
      78,    79,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    54,     0,    28,    31,     0,    49,
      52,    37,    35,    50,    56,     0,    80,    75,    74,    76,
      77,    70,    71,    72,    73,     0,     0,    65,    69,     0,
      53,    60,    92,     0,     0,    88,     0,     0,     0,    64,
      66,    48,     0,    90,    91,     0,     0,     0,     0,    67,
      94,    89,     0,     0,    62,     0,     0,    68,    63,    93
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -59,   -59,   -59,   133,   -59,   -59,   -59,   121,   -59,   125,
     126,   -59,   -58,   -59,   -59,   -59,   -59,    57,   -59,   -31,
     -59,   -59,    65,   -59,   -59,   -59,   -22,   -59,   -59,   -59,
     -59,   -59,     7,   -59,   -32
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     2,     3,     4,    12,    27,    13,    14,    17,    18,
      19,    57,    38,    39,    86,    87,    40,    66,    67,    41,
      42,    43,    44,    45,    46,    47,    79,    97,    98,    49,
      50,   149,   150,    51,    80
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      48,    81,    83,    29,    70,    92,    88,   104,    30,    71,
      72,    73,    74,    75,    31,    48,    32,     1,    89,    33,
      34,    35,    68,    76,    69,   104,     7,    36,     9,    77,
      90,    10,   111,     5,     6,    78,    96,    99,    82,   147,
     148,    48,   -30,    11,   100,   101,   102,   109,   110,    15,
     111,   147,   158,   115,   137,   138,   117,   118,    16,    21,
     104,   121,    52,    20,    26,    48,    22,    53,    54,    55,
      56,   127,   128,   129,   130,   131,   132,   133,   134,   136,
     107,   108,   109,   110,    29,   111,    23,    24,    58,    30,
      48,    48,    25,   141,    60,    31,    62,    32,    63,   164,
      33,    34,    35,   144,    64,   167,    65,   168,    36,    84,
      91,   152,    85,    93,   155,   156,    29,    94,    69,    95,
     119,    30,   157,   -29,   124,   116,   125,    31,   111,    32,
     166,    68,    33,    34,    35,    48,     8,   151,   165,    70,
      36,    48,    28,    48,    71,    72,    73,    74,    75,    59,
     103,    61,   122,   104,    37,   120,   159,     0,    76,     0,
       0,     0,     0,     0,    77,     0,   105,   106,     0,   142,
      78,     0,   143,   107,   108,   109,   110,     0,   111,    70,
       0,     0,     0,   114,    71,    72,    73,    74,    75,     0,
     103,     0,     0,   104,     0,     0,     0,     0,    76,     0,
       0,     0,     0,     0,    77,   103,   105,   106,   104,     0,
      78,     0,   135,   107,   108,   109,   110,     0,   111,     0,
       0,   105,   106,   140,   103,     0,     0,   104,   107,   108,
     109,   110,     0,   111,   145,     0,     0,   146,     0,     0,
     105,   106,   103,     0,     0,   104,     0,   107,   108,   109,
     110,     0,   111,   161,     0,     0,   162,     0,   105,   106,
     103,     0,     0,   104,     0,   107,   108,   109,   110,     0,
     111,     0,     0,     0,   112,     0,   105,   106,   103,     0,
       0,   104,     0,   107,   108,   109,   110,     0,   111,     0,
       0,     0,   113,     0,   105,   106,   103,     0,     0,   104,
       0,   107,   108,   109,   110,     0,   111,     0,     0,     0,
     163,     0,   105,   106,   103,     0,     0,   104,     0,   107,
     108,   109,   110,     0,   111,     0,     0,   126,     0,   103,
     105,   106,   104,     0,     0,     0,     0,   107,   108,   109,
     110,    70,   111,     0,     0,   139,    71,    72,    73,    74,
      75,     0,   107,   108,   109,   110,    70,   111,     0,     0,
      76,    71,    72,    73,    74,    75,    77,   103,     0,     0,
     104,   154,    78,     0,     0,    76,     0,     0,     0,     0,
       0,    77,   103,   105,   106,   104,     0,    78,     0,     0,
     107,   108,   109,   110,     0,   111,   123,   103,   105,   106,
     104,     0,     0,     0,     0,   107,   108,   109,   110,     0,
     111,   153,   103,   105,   106,   104,     0,     0,     0,     0,
     107,   108,   109,   110,     0,   111,   160,   103,   105,   106,
     104,     0,     0,     0,     0,   107,   108,   109,   110,     0,
     111,   169,   103,   105,   106,   104,     0,     0,     0,     0,
     107,   108,   109,   110,     0,   111,     0,     0,   105,     0,
       0,     0,     0,     0,     0,   107,   108,   109,   110,     0,
     111
};

static const yytype_int16 yycheck[] =
{
      22,    33,    34,     1,     3,    63,    37,     7,     6,     8,
       9,    10,    11,    12,    12,    37,    14,     5,    26,    17,
      18,    19,    32,    22,    34,     7,     0,    25,    34,    28,
      38,    34,    32,    12,    13,    34,    68,    69,    37,    15,
      16,    63,    40,     6,    76,    77,    78,    29,    30,    35,
      32,    15,    16,    85,   112,   113,    87,    89,    12,    37,
       7,    93,     3,    35,    24,    87,    36,     8,     9,    10,
      11,   103,   104,   105,   106,   107,   108,   109,   110,   111,
      27,    28,    29,    30,     1,    32,    36,    38,    12,     6,
     112,   113,    38,   125,    12,    12,     6,    14,    36,   157,
      17,    18,    19,   135,    37,   163,    12,   165,    25,    37,
      37,   143,    34,    26,   146,   147,     1,    37,    34,    38,
      12,     6,    36,    40,    35,    40,    38,    12,    32,    14,
     162,    32,    17,    18,    19,   157,     3,    37,    36,     3,
      25,   163,    21,   165,     8,     9,    10,    11,    12,    24,
       4,    25,    95,     7,    39,    90,   149,    -1,    22,    -1,
      -1,    -1,    -1,    -1,    28,    -1,    20,    21,    -1,    33,
      34,    -1,    36,    27,    28,    29,    30,    -1,    32,     3,
      -1,    -1,    -1,    37,     8,     9,    10,    11,    12,    -1,
       4,    -1,    -1,     7,    -1,    -1,    -1,    -1,    22,    -1,
      -1,    -1,    -1,    -1,    28,     4,    20,    21,     7,    -1,
      34,    -1,    36,    27,    28,    29,    30,    -1,    32,    -1,
      -1,    20,    21,    37,     4,    -1,    -1,     7,    27,    28,
      29,    30,    -1,    32,    33,    -1,    -1,    36,    -1,    -1,
      20,    21,     4,    -1,    -1,     7,    -1,    27,    28,    29,
      30,    -1,    32,    33,    -1,    -1,    36,    -1,    20,    21,
       4,    -1,    -1,     7,    -1,    27,    28,    29,    30,    -1,
      32,    -1,    -1,    -1,    36,    -1,    20,    21,     4,    -1,
      -1,     7,    -1,    27,    28,    29,    30,    -1,    32,    -1,
      -1,    -1,    36,    -1,    20,    21,     4,    -1,    -1,     7,
      -1,    27,    28,    29,    30,    -1,    32,    -1,    -1,    -1,
      36,    -1,    20,    21,     4,    -1,    -1,     7,    -1,    27,
      28,    29,    30,    -1,    32,    -1,    -1,    35,    -1,     4,
      20,    21,     7,    -1,    -1,    -1,    -1,    27,    28,    29,
      30,     3,    32,    -1,    -1,    35,     8,     9,    10,    11,
      12,    -1,    27,    28,    29,    30,     3,    32,    -1,    -1,
      22,     8,     9,    10,    11,    12,    28,     4,    -1,    -1,
       7,    33,    34,    -1,    -1,    22,    -1,    -1,    -1,    -1,
      -1,    28,     4,    20,    21,     7,    -1,    34,    -1,    -1,
      27,    28,    29,    30,    -1,    32,    33,     4,    20,    21,
       7,    -1,    -1,    -1,    -1,    27,    28,    29,    30,    -1,
      32,    33,     4,    20,    21,     7,    -1,    -1,    -1,    -1,
      27,    28,    29,    30,    -1,    32,    33,     4,    20,    21,
       7,    -1,    -1,    -1,    -1,    27,    28,    29,    30,    -1,
      32,    33,     4,    20,    21,     7,    -1,    -1,    -1,    -1,
      27,    28,    29,    30,    -1,    32,    -1,    -1,    20,    -1,
      -1,    -1,    -1,    -1,    -1,    27,    28,    29,    30,    -1,
      32
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     5,    42,    43,    44,    12,    13,     0,    44,    34,
      34,     6,    45,    47,    48,    35,    12,    49,    50,    51,
      35,    37,    36,    36,    38,    38,    24,    46,    48,     1,
       6,    12,    14,    17,    18,    19,    25,    39,    53,    54,
      57,    60,    61,    62,    63,    64,    65,    66,    67,    70,
      71,    74,     3,     8,     9,    10,    11,    52,    12,    50,
      12,    51,     6,    36,    37,    12,    58,    59,    32,    34,
       3,     8,     9,    10,    11,    12,    22,    28,    34,    67,
      75,    75,    37,    75,    37,    34,    55,    56,    60,    26,
      38,    37,    53,    26,    37,    38,    75,    68,    69,    75,
      75,    75,    75,     4,     7,    20,    21,    27,    28,    29,
      30,    32,    36,    36,    37,    75,    40,    60,    75,    12,
      63,    75,    58,    33,    35,    38,    35,    75,    75,    75,
      75,    75,    75,    75,    75,    36,    75,    53,    53,    35,
      37,    75,    33,    36,    75,    33,    36,    15,    16,    72,
      73,    37,    75,    33,    33,    75,    75,    36,    16,    73,
      33,    33,    36,    36,    53,    36,    75,    53,    53,    33
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    41,    42,    43,    43,    44,    44,    45,    45,    46,
      46,    47,    47,    48,    48,    48,    49,    49,    50,    50,
      51,    52,    52,    52,    52,    52,    53,    53,    54,    55,
      55,    56,    56,    57,    58,    58,    59,    59,    60,    60,
      60,    60,    60,    60,    60,    60,    60,    61,    62,    63,
      63,    64,    64,    65,    66,    66,    67,    68,    68,    69,
      69,    70,    71,    71,    71,    71,    72,    72,    73,    74,
      75,    75,    75,    75,    75,    75,    75,    75,    75,    75,
      75,    75,    75,    75,    75,    75,    75,    75,    75,    75,
      75,    75,    75,    75,    75
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     1,     8,     6,     1,     0,     2,
       0,     1,     3,     2,     4,     2,     1,     3,     1,     3,
       3,     1,     1,     1,     1,     1,     1,     1,     3,     1,
       0,     2,     1,     3,     1,     3,     1,     3,     1,     1,
       1,     1,     1,     1,     1,     1,     2,     2,     5,     1,
       4,     1,     3,     4,     3,     2,     4,     1,     0,     1,
       3,     2,     7,     8,     5,     4,     1,     2,     4,     4,
       3,     3,     3,     3,     3,     3,     3,     3,     2,     2,
       3,     1,     1,     1,     1,     1,     1,     1,     4,     6,
       5,     5,     4,     8,     6
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* CODE: FUNC_LIST  */
#line 57 "compiler.y"
                { 
    (yyval.n) = mknode("CODE", (yyvsp[0].n), NULL); 
    ast_root = (yyval.n); 
}
#line 1337 "compiler.tab.c"
    break;

  case 3: /* FUNC_LIST: FUNC_LIST FUNC  */
#line 62 "compiler.y"
                          { (yyval.n) = mknode("FUNC_LIST", (yyvsp[-1].n), (yyvsp[0].n)); }
#line 1343 "compiler.tab.c"
    break;

  case 4: /* FUNC_LIST: FUNC  */
#line 63 "compiler.y"
                          { (yyval.n) = (yyvsp[0].n); }
#line 1349 "compiler.tab.c"
    break;

  case 5: /* FUNC: DEF ID '(' ARGS ')' RET_TYPE ':' SUITE  */
#line 65 "compiler.y"
                                             {
    (yyval.n) = mknode("FUNC", (yyvsp[-6].n), mknode("ARGS", (yyvsp[-4].n), mknode((yyvsp[-2].n)->token, (yyvsp[-2].n)->left, (yyvsp[0].n))));
}
#line 1357 "compiler.tab.c"
    break;

  case 6: /* FUNC: DEF MAIN_ID '(' ')' ':' SUITE  */
#line 68 "compiler.y"
                                {
    (yyval.n) = mknode("FUNC", (yyvsp[-4].n), mknode("ARGS", mknode("NONE", NULL, NULL), mknode("RETURN VOID", NULL, (yyvsp[0].n))));
}
#line 1365 "compiler.tab.c"
    break;

  case 7: /* ARGS: PARAMS  */
#line 72 "compiler.y"
             { (yyval.n) = (yyvsp[0].n); }
#line 1371 "compiler.tab.c"
    break;

  case 8: /* ARGS: %empty  */
#line 73 "compiler.y"
              { (yyval.n) = mknode("NONE", NULL, NULL); }
#line 1377 "compiler.tab.c"
    break;

  case 9: /* RET_TYPE: ARROW TOKEN_TYPE  */
#line 75 "compiler.y"
                           { (yyval.n) = mknode("RET", (yyvsp[0].n), NULL); }
#line 1383 "compiler.tab.c"
    break;

  case 10: /* RET_TYPE: %empty  */
#line 76 "compiler.y"
                           { (yyval.n) = mknode("RETURN VOID", NULL, NULL); }
#line 1389 "compiler.tab.c"
    break;

  case 11: /* PARAMS: TYPE_GROUP  */
#line 78 "compiler.y"
                                { (yyval.n) = (yyvsp[0].n); }
#line 1395 "compiler.tab.c"
    break;

  case 12: /* PARAMS: PARAMS ';' TYPE_GROUP  */
#line 79 "compiler.y"
                                { (yyval.n) = mknode("PARAMS", (yyvsp[-2].n), (yyvsp[0].n)); }
#line 1401 "compiler.tab.c"
    break;

  case 13: /* TYPE_GROUP: TOKEN_TYPE BARE_PARAM_LIST  */
#line 81 "compiler.y"
                                                    { (yyval.n) = mknode((yyvsp[-1].n)->token, (yyvsp[0].n), NULL); }
#line 1407 "compiler.tab.c"
    break;

  case 14: /* TYPE_GROUP: TOKEN_TYPE BARE_PARAM_LIST ',' DEFAULT_PARAM_LIST  */
#line 82 "compiler.y"
                                                              { (yyval.n) = mknode((yyvsp[-3].n)->token, mknode("BARE", (yyvsp[-2].n), (yyvsp[0].n)), NULL); }
#line 1413 "compiler.tab.c"
    break;

  case 15: /* TYPE_GROUP: TOKEN_TYPE DEFAULT_PARAM_LIST  */
#line 83 "compiler.y"
                                                    { (yyval.n) = mknode((yyvsp[-1].n)->token, (yyvsp[0].n), NULL); }
#line 1419 "compiler.tab.c"
    break;

  case 16: /* BARE_PARAM_LIST: ID  */
#line 85 "compiler.y"
                                             { (yyval.n) = (yyvsp[0].n); }
#line 1425 "compiler.tab.c"
    break;

  case 17: /* BARE_PARAM_LIST: BARE_PARAM_LIST ',' ID  */
#line 86 "compiler.y"
                                             { (yyval.n) = append_node((yyvsp[-2].n), (yyvsp[0].n)); }
#line 1431 "compiler.tab.c"
    break;

  case 18: /* DEFAULT_PARAM_LIST: PARAM_WITH_DEFAULT  */
#line 88 "compiler.y"
                                              { (yyval.n) = (yyvsp[0].n); }
#line 1437 "compiler.tab.c"
    break;

  case 19: /* DEFAULT_PARAM_LIST: DEFAULT_PARAM_LIST ',' PARAM_WITH_DEFAULT  */
#line 89 "compiler.y"
                                                              { (yyval.n) = mknode((yyvsp[-2].n)->token, (yyvsp[-2].n), (yyvsp[0].n)); }
#line 1443 "compiler.tab.c"
    break;

  case 20: /* PARAM_WITH_DEFAULT: ID ':' LITERAL  */
#line 91 "compiler.y"
                                              { (yyval.n) = mknode("DEFAULT", (yyvsp[-2].n), (yyvsp[0].n)); }
#line 1449 "compiler.tab.c"
    break;

  case 21: /* LITERAL: INT_LIT  */
#line 93 "compiler.y"
                      { (yyval.n) = (yyvsp[0].n); }
#line 1455 "compiler.tab.c"
    break;

  case 22: /* LITERAL: HEX_LIT  */
#line 94 "compiler.y"
                      { (yyval.n) = (yyvsp[0].n); }
#line 1461 "compiler.tab.c"
    break;

  case 23: /* LITERAL: FLOAT_LIT  */
#line 95 "compiler.y"
                      { (yyval.n) = (yyvsp[0].n); }
#line 1467 "compiler.tab.c"
    break;

  case 24: /* LITERAL: STRING_LIT  */
#line 96 "compiler.y"
                      { (yyval.n) = (yyvsp[0].n); }
#line 1473 "compiler.tab.c"
    break;

  case 25: /* LITERAL: BOOL_LIT  */
#line 97 "compiler.y"
                      { (yyval.n) = (yyvsp[0].n); }
#line 1479 "compiler.tab.c"
    break;

  case 26: /* SUITE: STMT  */
#line 99 "compiler.y"
             { (yyval.n) = (yyvsp[0].n); }
#line 1485 "compiler.tab.c"
    break;

  case 27: /* SUITE: BLOCK  */
#line 100 "compiler.y"
             { (yyval.n) = (yyvsp[0].n); }
#line 1491 "compiler.tab.c"
    break;

  case 28: /* BLOCK: '{' BODY '}'  */
#line 102 "compiler.y"
                    { (yyval.n) = (yyvsp[-1].n); }
#line 1497 "compiler.tab.c"
    break;

  case 29: /* BODY: STMT_LIST  */
#line 104 "compiler.y"
                { (yyval.n) = mknode("BODY", (yyvsp[0].n), NULL); }
#line 1503 "compiler.tab.c"
    break;

  case 30: /* BODY: %empty  */
#line 105 "compiler.y"
                { (yyval.n) = mknode("BODY", NULL, NULL); }
#line 1509 "compiler.tab.c"
    break;

  case 31: /* STMT_LIST: STMT_LIST STMT  */
#line 107 "compiler.y"
                          { (yyval.n) = mknode("STMT_LIST", (yyvsp[-1].n), (yyvsp[0].n)); }
#line 1515 "compiler.tab.c"
    break;

  case 32: /* STMT_LIST: STMT  */
#line 108 "compiler.y"
                { (yyval.n) = (yyvsp[0].n); }
#line 1521 "compiler.tab.c"
    break;

  case 33: /* DECLARATION: TOKEN_TYPE DECL_LIST ';'  */
#line 110 "compiler.y"
                                      { (yyval.n) = mknode((yyvsp[-2].n)->token, (yyvsp[-1].n), NULL); }
#line 1527 "compiler.tab.c"
    break;

  case 34: /* DECL_LIST: DECL_ITEM  */
#line 112 "compiler.y"
                                     { (yyval.n) = (yyvsp[0].n); }
#line 1533 "compiler.tab.c"
    break;

  case 35: /* DECL_LIST: DECL_ITEM ',' DECL_LIST  */
#line 113 "compiler.y"
                                     { (yyval.n) = mknode("DECL_LIST", (yyvsp[-2].n), (yyvsp[0].n)); }
#line 1539 "compiler.tab.c"
    break;

  case 36: /* DECL_ITEM: ID  */
#line 115 "compiler.y"
                                     { (yyval.n) = (yyvsp[0].n); }
#line 1545 "compiler.tab.c"
    break;

  case 37: /* DECL_ITEM: ID '=' EXPR  */
#line 116 "compiler.y"
                                     { (yyval.n) = mknode("ASSIGN", (yyvsp[-2].n), (yyvsp[0].n)); }
#line 1551 "compiler.tab.c"
    break;

  case 38: /* STMT: FUNC_CALL_STMT  */
#line 119 "compiler.y"
                     { (yyval.n) = (yyvsp[0].n); }
#line 1557 "compiler.tab.c"
    break;

  case 39: /* STMT: ASSIGNMENT  */
#line 120 "compiler.y"
                     { (yyval.n) = (yyvsp[0].n); }
#line 1563 "compiler.tab.c"
    break;

  case 40: /* STMT: DECLARATION  */
#line 121 "compiler.y"
                     { (yyval.n) = (yyvsp[0].n); }
#line 1569 "compiler.tab.c"
    break;

  case 41: /* STMT: RETURN_STMT  */
#line 122 "compiler.y"
                     { (yyval.n) = (yyvsp[0].n); }
#line 1575 "compiler.tab.c"
    break;

  case 42: /* STMT: IF_STMT  */
#line 123 "compiler.y"
                     { (yyval.n) = (yyvsp[0].n); }
#line 1581 "compiler.tab.c"
    break;

  case 43: /* STMT: WHILE_STMT  */
#line 124 "compiler.y"
                     { (yyval.n) = (yyvsp[0].n); }
#line 1587 "compiler.tab.c"
    break;

  case 44: /* STMT: PRINT_STMT  */
#line 125 "compiler.y"
                     { (yyval.n) = (yyvsp[0].n); }
#line 1593 "compiler.tab.c"
    break;

  case 45: /* STMT: PASS  */
#line 126 "compiler.y"
                     { (yyval.n) = (yyvsp[0].n); }
#line 1599 "compiler.tab.c"
    break;

  case 46: /* STMT: error ';'  */
#line 127 "compiler.y"
                     { yyerror("Error in statement"); yyerrok; }
#line 1605 "compiler.tab.c"
    break;

  case 47: /* PASS: TOKEN_PASS ';'  */
#line 129 "compiler.y"
                     { (yyval.n) = mknode("PASS", (yyvsp[-1].n), NULL); }
#line 1611 "compiler.tab.c"
    break;

  case 48: /* PRINT_STMT: PRINT '(' EXPR ')' ';'  */
#line 131 "compiler.y"
                                   { (yyval.n) = mknode("PRINT", (yyvsp[-2].n), NULL); }
#line 1617 "compiler.tab.c"
    break;

  case 49: /* LHS: ID  */
#line 133 "compiler.y"
                            { (yyval.n) = (yyvsp[0].n); }
#line 1623 "compiler.tab.c"
    break;

  case 50: /* LHS: ID '[' EXPR ']'  */
#line 134 "compiler.y"
                           { (yyval.n) = mknode("INDEX", (yyvsp[-3].n), (yyvsp[-1].n)); }
#line 1629 "compiler.tab.c"
    break;

  case 51: /* LHS_LIST: LHS  */
#line 136 "compiler.y"
                                  { (yyval.n) = (yyvsp[0].n); }
#line 1635 "compiler.tab.c"
    break;

  case 52: /* LHS_LIST: LHS_LIST ',' LHS  */
#line 137 "compiler.y"
                                 { (yyval.n) = mknode("LHS_LIST", (yyvsp[-2].n), (yyvsp[0].n)); }
#line 1641 "compiler.tab.c"
    break;

  case 53: /* ASSIGNMENT: LHS_LIST '=' EXPR ';'  */
#line 139 "compiler.y"
                                  { (yyval.n) = mknode("ASS", (yyvsp[-3].n), (yyvsp[-1].n)); }
#line 1647 "compiler.tab.c"
    break;

  case 54: /* RETURN_STMT: RETURN EXPR ';'  */
#line 141 "compiler.y"
                             { (yyval.n) = mknode("RET", (yyvsp[-1].n), NULL); }
#line 1653 "compiler.tab.c"
    break;

  case 55: /* RETURN_STMT: RETURN ';'  */
#line 142 "compiler.y"
                             { (yyval.n) = mknode("RET", NULL, NULL); }
#line 1659 "compiler.tab.c"
    break;

  case 56: /* FUNC_CALL: ID '(' ARG_LIST ')'  */
#line 144 "compiler.y"
                               { (yyval.n) = mknode("CALL", (yyvsp[-3].n), (yyvsp[-1].n)); }
#line 1665 "compiler.tab.c"
    break;

  case 57: /* ARG_LIST: EXPR_LIST  */
#line 146 "compiler.y"
                    { (yyval.n) = mknode("ARGS", (yyvsp[0].n), NULL); }
#line 1671 "compiler.tab.c"
    break;

  case 58: /* ARG_LIST: %empty  */
#line 147 "compiler.y"
                    { (yyval.n) = mknode("ARGS", mknode("NONE", NULL, NULL), NULL); }
#line 1677 "compiler.tab.c"
    break;

  case 59: /* EXPR_LIST: EXPR  */
#line 149 "compiler.y"
                                 { (yyval.n) = (yyvsp[0].n); }
#line 1683 "compiler.tab.c"
    break;

  case 60: /* EXPR_LIST: EXPR_LIST ',' EXPR  */
#line 150 "compiler.y"
                                { (yyval.n) = mknode("EXPR_LIST", (yyvsp[-2].n), (yyvsp[0].n)); }
#line 1689 "compiler.tab.c"
    break;

  case 61: /* FUNC_CALL_STMT: FUNC_CALL ';'  */
#line 152 "compiler.y"
                              { (yyval.n) = (yyvsp[-1].n); }
#line 1695 "compiler.tab.c"
    break;

  case 62: /* IF_STMT: IF EXPR ':' SUITE ELSE ':' SUITE  */
#line 155 "compiler.y"
                                             { (yyval.n) = mknode("IF-ELSE", (yyvsp[-5].n), mknode("BLOCK", (yyvsp[-3].n), (yyvsp[0].n))); }
#line 1701 "compiler.tab.c"
    break;

  case 63: /* IF_STMT: IF EXPR ':' SUITE ELIF_LIST ELSE ':' SUITE  */
#line 156 "compiler.y"
                                               { (yyval.n) = mknode("IF-ELIF-ELSE", (yyvsp[-6].n), mknode("CHAIN", (yyvsp[-4].n), mknode("ELIFS", (yyvsp[-3].n), (yyvsp[0].n)))); }
#line 1707 "compiler.tab.c"
    break;

  case 64: /* IF_STMT: IF EXPR ':' SUITE ELIF_LIST  */
#line 157 "compiler.y"
                                             { (yyval.n) = mknode("IF-ELIF", (yyvsp[-3].n), mknode("CHAIN", (yyvsp[-1].n), (yyvsp[0].n))); }
#line 1713 "compiler.tab.c"
    break;

  case 65: /* IF_STMT: IF EXPR ':' SUITE  */
#line 158 "compiler.y"
                                              { (yyval.n) = mknode("IF", (yyvsp[-2].n), (yyvsp[0].n)); }
#line 1719 "compiler.tab.c"
    break;

  case 66: /* ELIF_LIST: ELIF_BLOCK  */
#line 161 "compiler.y"
                                              { (yyval.n) = (yyvsp[0].n); }
#line 1725 "compiler.tab.c"
    break;

  case 67: /* ELIF_LIST: ELIF_LIST ELIF_BLOCK  */
#line 162 "compiler.y"
                                              { (yyval.n) = mknode("ELIF_LIST", (yyvsp[-1].n), (yyvsp[0].n)); }
#line 1731 "compiler.tab.c"
    break;

  case 68: /* ELIF_BLOCK: ELIF EXPR ':' SUITE  */
#line 165 "compiler.y"
                                              { (yyval.n) = mknode("ELIF", (yyvsp[-2].n), (yyvsp[0].n)); }
#line 1737 "compiler.tab.c"
    break;

  case 69: /* WHILE_STMT: WHILE EXPR ':' SUITE  */
#line 167 "compiler.y"
                                 { (yyval.n) = mknode("WHILE", (yyvsp[-2].n), (yyvsp[0].n)); }
#line 1743 "compiler.tab.c"
    break;

  case 70: /* EXPR: EXPR '+' EXPR  */
#line 169 "compiler.y"
                                { (yyval.n) = mknode("+", (yyvsp[-2].n), (yyvsp[0].n)); }
#line 1749 "compiler.tab.c"
    break;

  case 71: /* EXPR: EXPR '-' EXPR  */
#line 170 "compiler.y"
                                { (yyval.n) = mknode("-", (yyvsp[-2].n), (yyvsp[0].n)); }
#line 1755 "compiler.tab.c"
    break;

  case 72: /* EXPR: EXPR '*' EXPR  */
#line 171 "compiler.y"
                                { (yyval.n) = mknode("*", (yyvsp[-2].n), (yyvsp[0].n)); }
#line 1761 "compiler.tab.c"
    break;

  case 73: /* EXPR: EXPR '/' EXPR  */
#line 172 "compiler.y"
                                { (yyval.n) = mknode("/", (yyvsp[-2].n), (yyvsp[0].n)); }
#line 1767 "compiler.tab.c"
    break;

  case 74: /* EXPR: EXPR POW EXPR  */
#line 173 "compiler.y"
                                { (yyval.n) = mknode("**", (yyvsp[-2].n), (yyvsp[0].n)); }
#line 1773 "compiler.tab.c"
    break;

  case 75: /* EXPR: EXPR REL_OP EXPR  */
#line 174 "compiler.y"
                                { (yyval.n) = mknode((yyvsp[-1].n)->token, (yyvsp[-2].n), (yyvsp[0].n)); }
#line 1779 "compiler.tab.c"
    break;

  case 76: /* EXPR: EXPR AND EXPR  */
#line 175 "compiler.y"
                                { (yyval.n) = mknode("AND", (yyvsp[-2].n), (yyvsp[0].n)); }
#line 1785 "compiler.tab.c"
    break;

  case 77: /* EXPR: EXPR OR EXPR  */
#line 176 "compiler.y"
                                { (yyval.n) = mknode("OR", (yyvsp[-2].n), (yyvsp[0].n)); }
#line 1791 "compiler.tab.c"
    break;

  case 78: /* EXPR: NOT EXPR  */
#line 177 "compiler.y"
                                { (yyval.n) = mknode("NOT", (yyvsp[0].n), NULL); }
#line 1797 "compiler.tab.c"
    break;

  case 79: /* EXPR: '-' EXPR  */
#line 178 "compiler.y"
                                { (yyval.n) = mknode("NEG", (yyvsp[0].n), NULL); }
#line 1803 "compiler.tab.c"
    break;

  case 80: /* EXPR: '(' EXPR ')'  */
#line 179 "compiler.y"
                                { (yyval.n) = (yyvsp[-1].n); }
#line 1809 "compiler.tab.c"
    break;

  case 81: /* EXPR: ID  */
#line 180 "compiler.y"
                                { (yyval.n) = (yyvsp[0].n); }
#line 1815 "compiler.tab.c"
    break;

  case 82: /* EXPR: INT_LIT  */
#line 181 "compiler.y"
                                { (yyval.n) = (yyvsp[0].n); }
#line 1821 "compiler.tab.c"
    break;

  case 83: /* EXPR: STRING_LIT  */
#line 182 "compiler.y"
                                { (yyval.n) = (yyvsp[0].n); }
#line 1827 "compiler.tab.c"
    break;

  case 84: /* EXPR: BOOL_LIT  */
#line 183 "compiler.y"
                                { (yyval.n) = (yyvsp[0].n); }
#line 1833 "compiler.tab.c"
    break;

  case 85: /* EXPR: FLOAT_LIT  */
#line 184 "compiler.y"
                                { (yyval.n) = (yyvsp[0].n); }
#line 1839 "compiler.tab.c"
    break;

  case 86: /* EXPR: HEX_LIT  */
#line 185 "compiler.y"
                                { (yyval.n) = (yyvsp[0].n); }
#line 1845 "compiler.tab.c"
    break;

  case 87: /* EXPR: FUNC_CALL  */
#line 186 "compiler.y"
                                { (yyval.n) = (yyvsp[0].n); }
#line 1851 "compiler.tab.c"
    break;

  case 88: /* EXPR: EXPR '[' EXPR ']'  */
#line 187 "compiler.y"
                                            { (yyval.n) = mknode("INDEX", (yyvsp[-3].n), (yyvsp[-1].n)); }
#line 1857 "compiler.tab.c"
    break;

  case 89: /* EXPR: EXPR '[' EXPR ':' EXPR ']'  */
#line 188 "compiler.y"
                                            { (yyval.n) = mknode("SLICE", (yyvsp[-5].n), mknode("RANGE", (yyvsp[-3].n), (yyvsp[-1].n))); }
#line 1863 "compiler.tab.c"
    break;

  case 90: /* EXPR: EXPR '[' ':' EXPR ']'  */
#line 189 "compiler.y"
                                            { (yyval.n) = mknode("SLICE", (yyvsp[-4].n), mknode("RANGE", mknode("START", NULL, NULL), (yyvsp[-1].n))); }
#line 1869 "compiler.tab.c"
    break;

  case 91: /* EXPR: EXPR '[' EXPR ':' ']'  */
#line 190 "compiler.y"
                                            { (yyval.n) = mknode("SLICE", (yyvsp[-4].n), mknode("RANGE", (yyvsp[-2].n), mknode("END", NULL, NULL))); }
#line 1875 "compiler.tab.c"
    break;

  case 92: /* EXPR: EXPR '[' ':' ']'  */
#line 191 "compiler.y"
                                            { (yyval.n) = mknode("SLICE", (yyvsp[-3].n), mknode("RANGE", mknode("START", NULL, NULL), mknode("END", NULL, NULL))); }
#line 1881 "compiler.tab.c"
    break;

  case 93: /* EXPR: EXPR '[' EXPR ':' EXPR ':' EXPR ']'  */
#line 192 "compiler.y"
                                            { (yyval.n) = mknode("SLICE", (yyvsp[-7].n), mknode("RANGE", (yyvsp[-5].n), mknode("STEP", (yyvsp[-3].n), (yyvsp[-1].n)))); }
#line 1887 "compiler.tab.c"
    break;

  case 94: /* EXPR: EXPR '[' ':' ':' EXPR ']'  */
#line 193 "compiler.y"
                                            { (yyval.n) = mknode("SLICE", (yyvsp[-5].n), mknode("RANGE", mknode("START", NULL, NULL), mknode("STEP", mknode("END", NULL, NULL), (yyvsp[-1].n)))); }
#line 1893 "compiler.tab.c"
    break;


#line 1897 "compiler.tab.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
    }

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 195 "compiler.y"


node* append_node(node* list, node* new_node) {
    if (!list) return new_node;
    
    if (strcmp(list->token, "PARAM_LIST") != 0) {
        return mknode("PARAM_LIST", list, new_node);
    }
    
    node* current = list;
    while (current && strcmp(current->token, "PARAM_LIST") == 0 && current->right) {
        current = current->right;
    }
    
    if (strcmp(current->token, "PARAM_LIST") != 0) {
        node* new_list = mknode("PARAM_LIST", current, new_node);
        return list == current ? new_list : list;
    }
    
    current->right = new_node;
    return list;
}

void printtree(node *tree, int level) {
    if (!tree) return;
    for (int i = 0; i < level; i++) printf("  ");
    printf("(%s", tree->token);
    if (tree->left || tree->right) {
        printf("\n");
        printtree(tree->left, level + 1);
        printtree(tree->right, level + 1);
        for (int i = 0; i < level; i++) printf("  ");
    }
    printf(")\n");
}

void yyerror(const char *msg) {
    extern int yylineno;
    extern char currentLineText[];
    extern int currentPos;

    syntax_error_occurred = 1;  
    
    fprintf(stderr, "\nSyntax error at line %d!\n", yylineno);
    fprintf(stderr, "%s\n", currentLineText);
    if (currentPos > 0) {
        for (int i = 0; i < currentPos; i++) fprintf(stderr, " ");
        fprintf(stderr, "^\n");
    }
}


char* generate_expr_code(node* expr) {
    if (!expr) return NULL;
    int temp_counter = 0;

    if (!expr->left && !expr->right) {
        if (expr->token[0] >= '0' && expr->token[0] <= '9') {
            char* temp = new_temp();
            printf("\t%s = %s\n", temp, expr->token);
            return temp;
        }
        if (strstr(expr->token, ".") != NULL) {
            char* temp = new_temp();
            printf("\t%s = %s\n", temp, expr->token);
            return temp;
        }
        return expr->token;
    }

    
    
    if (strcmp(expr->token, "+") == 0 || strcmp(expr->token, "-") == 0 ||
        strcmp(expr->token, "*") == 0 || strcmp(expr->token, "/") == 0) {
        char* left_temp = generate_expr_code(expr->left);
        char* right_temp = generate_expr_code(expr->right);
        char* result_temp = new_temp();
        printf("\t%s = %s %s %s\n", result_temp, left_temp, expr->token, right_temp);
        return result_temp;
    }
    
    if (strcmp(expr->token, "==") == 0 || strcmp(expr->token, "!=") == 0 ||
        strcmp(expr->token, "<") == 0 || strcmp(expr->token, ">") == 0 ||
        strcmp(expr->token, "<=") == 0 || strcmp(expr->token, ">=") == 0) {
        return NULL; 
    }
    
    if (strcmp(expr->token, "CALL") == 0) {
        param_count = 0;
        node* args = expr->right;
        if (args && args->left && strcmp(args->left->token, "NONE") != 0) {
            node* arg = args->left;
            while (arg) {
                if (strcmp(arg->token, "EXPR_LIST") == 0) {
                    char* temp = generate_expr_code(arg->left);
                    printf("\tPushParam %s\n", temp);
                    param_count++;
                    arg = arg->right;
                } else {
                    char* temp = generate_expr_code(arg);
                    printf("\tPushParam %s\n", temp);
                    param_count++;
                    break;
                }
            }
        }
        
        char* result_temp = new_temp();
        printf("\t%s = LCall %s\n", result_temp, expr->left->token);
        printf("\tPopParams %d\n", param_count * 8);
        
        return result_temp;
    }
    
    return expr->token;
}


void generate_stmt_code(node* stmt) {
    if (!stmt) return;
    
    if (strcmp(stmt->token, "STMT_LIST") == 0) {
        generate_stmt_code(stmt->left);
        generate_stmt_code(stmt->right);
        return;
    }
    
    if (strcmp(stmt->token, "BODY") == 0) {
        generate_stmt_code(stmt->left);
        return;
    }
    
    if (strcmp(stmt->token, "int") == 0 || strcmp(stmt->token, "float") == 0) {
        node* decl = stmt->left;
        while (decl) {
            if (strcmp(decl->token, "ASSIGN") == 0) {
                char* expr_result = generate_expr_code(decl->right);
                if (expr_result && decl->left) {
                    printf("\t%s = %s\n", decl->left->token, expr_result);
                }
            }
            if (strcmp(decl->token, "DECL_LIST") == 0) {
                decl = decl->right;
            } else {
                break;
            }
        }
        return;
    }
    
    if (strcmp(stmt->token, "ASS") == 0) {
        char* expr_result = generate_expr_code(stmt->right);
        if (expr_result && stmt->left) {
            printf("\t%s = %s\n", stmt->left->token, expr_result);
        }
        return;
    }
    
    if (strcmp(stmt->token, "IF") == 0 || 
        strcmp(stmt->token, "IF-ELSE") == 0 ||
        strcmp(stmt->token, "IF-ELIF") == 0 ||
        strcmp(stmt->token, "IF-ELIF-ELSE") == 0) {
        
        char* end_label = new_label();
        
        char* true_label = new_label();
        char* false_label = new_label();
        
        if (stmt->left && stmt->left->token) {
            char* op = stmt->left->token;
            char* left = generate_expr_code(stmt->left->left);
            char* right = generate_expr_code(stmt->left->right);
            printf("\tif %s %s %s Goto %s\n", left, op, right, true_label);
            printf("\tGoto %s\n", false_label);
        }
        
        printf("%s:\n", true_label);
        if (strcmp(stmt->token, "IF") == 0) {
            generate_stmt_code(stmt->right);
        } else {
            if (stmt->right && stmt->right->left) {
                generate_stmt_code(stmt->right->left);
            }
        }
        printf("\tGoto %s\n", end_label);
        
        printf("%s:\n", false_label);
        
        if (strcmp(stmt->token, "IF-ELSE") == 0) {
            if (stmt->right && stmt->right->right) {
                generate_stmt_code(stmt->right->right);
            }
        } else if (strcmp(stmt->token, "IF-ELIF") == 0 || 
                   strcmp(stmt->token, "IF-ELIF-ELSE") == 0) {
            node* elif_chain = NULL;
            if (strcmp(stmt->token, "IF-ELIF") == 0) {
                elif_chain = stmt->right->right;
            } else {
                if (stmt->right && stmt->right->right && stmt->right->right->left) {
                    elif_chain = stmt->right->right->left;
                }
            }
            
            while (elif_chain) {
                if (strcmp(elif_chain->token, "ELIF") == 0) {
                    char* elif_true = new_label();
                    char* elif_false = new_label();
                    
                    if (elif_chain->left && elif_chain->left->token) {
                        char* op = elif_chain->left->token;
                        char* left = generate_expr_code(elif_chain->left->left);
                        char* right = generate_expr_code(elif_chain->left->right);
                        printf("\tif %s %s %s Goto %s\n", left, op, right, elif_true);
                        printf("\tGoto %s\n", elif_false);
                    }
                    
                    printf("%s:\n", elif_true);
                    generate_stmt_code(elif_chain->right);
                    printf("\tGoto %s\n", end_label);
                    
                    printf("%s:\n", elif_false);
                    break;
                } else if (strcmp(elif_chain->token, "ELIF_LIST") == 0) {
                    node* current_elif = elif_chain->left;
                    if (current_elif && strcmp(current_elif->token, "ELIF") == 0) {
                        char* elif_true = new_label();
                        char* elif_false = new_label();
                        
                        if (current_elif->left && current_elif->left->token) {
                            char* op = current_elif->left->token;
                            char* left = generate_expr_code(current_elif->left->left);
                            char* right = generate_expr_code(current_elif->left->right);
                            printf("\tif %s %s %s Goto %s\n", left, op, right, elif_true);
                            printf("\tGoto %s\n", elif_false);
                        }
                        
                        printf("%s:\n", elif_true);
                        generate_stmt_code(current_elif->right);
                        printf("\tGoto %s\n", end_label);
                        
                        printf("%s:\n", elif_false);
                    }
                    elif_chain = elif_chain->right;
                } else {
                    break;
                }
            }
            
            if (strcmp(stmt->token, "IF-ELIF-ELSE") == 0) {
                if (stmt->right && stmt->right->right && stmt->right->right->right) {
                    generate_stmt_code(stmt->right->right->right);
                }
            }
        }
        
        printf("%s:\n", end_label);
        return;
    }
    
    if (strcmp(stmt->token, "WHILE") == 0) {
        char* loop_label = new_label();
        char* body_label = new_label();
        char* exit_label = new_label();
        
        printf("%s:\n", loop_label);
        
        if (stmt->left && stmt->left->token) {
            char* op = stmt->left->token;
            char* left = generate_expr_code(stmt->left->left);
            char* right = generate_expr_code(stmt->left->right);
            printf("\tif %s %s %s Goto %s\n", left, op, right, body_label);
            printf("\tGoto %s\n", exit_label);
        }
        
        printf("%s:\n", body_label);
        if (stmt->right) {
            generate_stmt_code(stmt->right);
        }
        printf("\tGoto %s\n", loop_label);
        
        printf("%s:\n", exit_label);
        return;
    }
    
    if (strcmp(stmt->token, "RET") == 0) {
        if (stmt->left) {
            char* ret_value = generate_expr_code(stmt->left);
            printf("\tReturn %s\n", ret_value);
        } else {
            printf("\tReturn\n");
        }
        return;
    }
    
    if (strcmp(stmt->token, "BLOCK") == 0) {
        generate_stmt_code(stmt->left);
        generate_stmt_code(stmt->right);
        return;
    }
    
    if (strcmp(stmt->token, "CALL") == 0) {
        generate_expr_code(stmt);
        return;
    }
}



void generate_func_code(node* func) {
    if (!func) return;
    
    if (strcmp(func->token, "FUNC") == 0) {
        char* func_name = func->left->token;
        printf("%s:\n", func_name);
        
        printf("\tBeginFunc %d\n", func_counter++);

        
        
        node* args_node = func->right;
        if (args_node && args_node->right) {
            node* ret_type_node = args_node->right;
            if (ret_type_node && ret_type_node->right) {
                generate_stmt_code(ret_type_node->right);
            }
        }
        
        printf("\tEndFunc\n");

    }
}

void generate_funcs_from_list(node* func_list) {
    if (!func_list) return;

    if (strcmp(func_list->token, "FUNC_LIST") == 0) {
        generate_funcs_from_list(func_list->left);
        generate_func_code(func_list->right);
    } else {
        generate_func_code(func_list);
    }
}

void generate_3ac_from_ast(node* root) {
    if (!root) return;

    if (strcmp(root->token, "CODE") == 0) {
        generate_funcs_from_list(root->left);
    }
}


int main() {
    extern int yydebug;
    yydebug = 0;
    
    int result = yyparse();
    
    if (result == 0 && syntax_error_occurred == 0 && ast_root != NULL) {
        int errors = analyze_tree(ast_root);
        
        if (errors > 0) {
            printf("Semantic errors found. Compilation failed.\n");
            exit(1);
        }
        
        generate_3ac_from_ast(ast_root);
        
        return 0;
    } else {
        printf("Parsing failed due to syntax errors\n");
        return 1;
    }
}
