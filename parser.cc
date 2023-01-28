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
#line 1 "rules/parser.y"

    #include "include/creol/ast.hh"
    #include "include/creol/cli.hh"

    #include <cstdio>
    #include <cstdlib>
    #include <iostream>

    extern int yylex();
    void yyerror(const char* err);

    using namespace creol;

    ast::BlockSttmt* Program;

#line 87 "parser.cc"

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

#include "parser.hh"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_IDENT = 3,                      /* IDENT  */
  YYSYMBOL_STR_LIT = 4,                    /* STR_LIT  */
  YYSYMBOL_MOSTRA = 5,                     /* MOSTRA  */
  YYSYMBOL_INT_LIT = 6,                    /* INT_LIT  */
  YYSYMBOL_FLOAT_LIT = 7,                  /* FLOAT_LIT  */
  YYSYMBOL_BOOL_LIT = 8,                   /* BOOL_LIT  */
  YYSYMBOL_PLUS = 9,                       /* PLUS  */
  YYSYMBOL_MINUS = 10,                     /* MINUS  */
  YYSYMBOL_MUL = 11,                       /* MUL  */
  YYSYMBOL_DIV = 12,                       /* DIV  */
  YYSYMBOL_EQ = 13,                        /* EQ  */
  YYSYMBOL_NE = 14,                        /* NE  */
  YYSYMBOL_LT = 15,                        /* LT  */
  YYSYMBOL_LE = 16,                        /* LE  */
  YYSYMBOL_GT = 17,                        /* GT  */
  YYSYMBOL_GE = 18,                        /* GE  */
  YYSYMBOL_AND = 19,                       /* AND  */
  YYSYMBOL_OR = 20,                        /* OR  */
  YYSYMBOL_ASSIGN = 21,                    /* ASSIGN  */
  YYSYMBOL_LCURLY = 22,                    /* LCURLY  */
  YYSYMBOL_RCURLY = 23,                    /* RCURLY  */
  YYSYMBOL_COMMA = 24,                     /* COMMA  */
  YYSYMBOL_SEMIC = 25,                     /* SEMIC  */
  YYSYMBOL_LBRAC = 26,                     /* LBRAC  */
  YYSYMBOL_RBRAC = 27,                     /* RBRAC  */
  YYSYMBOL_TYPE_INT = 28,                  /* TYPE_INT  */
  YYSYMBOL_TYPE_FLOAT = 29,                /* TYPE_FLOAT  */
  YYSYMBOL_TYPE_BOOL = 30,                 /* TYPE_BOOL  */
  YYSYMBOL_TYPE_VOID = 31,                 /* TYPE_VOID  */
  YYSYMBOL_DIVOLVI = 32,                   /* DIVOLVI  */
  YYSYMBOL_DI = 33,                        /* DI  */
  YYSYMBOL_STRUT = 34,                     /* STRUT  */
  YYSYMBOL_NKUANTU = 35,                   /* NKUANTU  */
  YYSYMBOL_SI = 36,                        /* SI  */
  YYSYMBOL_SINON = 37,                     /* SINON  */
  YYSYMBOL_IMPRISTAN = 38,                 /* IMPRISTAN  */
  YYSYMBOL_PARA = 39,                      /* PARA  */
  YYSYMBOL_CONTINUA = 40,                  /* CONTINUA  */
  YYSYMBOL_DOT = 41,                       /* DOT  */
  YYSYMBOL_RPAR = 42,                      /* RPAR  */
  YYSYMBOL_LPAR = 43,                      /* LPAR  */
  YYSYMBOL_UMINUS = 44,                    /* UMINUS  */
  YYSYMBOL_YYACCEPT = 45,                  /* $accept  */
  YYSYMBOL_program = 46,                   /* program  */
  YYSYMBOL_type_specifier = 47,            /* type_specifier  */
  YYSYMBOL_constant = 48,                  /* constant  */
  YYSYMBOL_identifier = 49,                /* identifier  */
  YYSYMBOL_declarator = 50,                /* declarator  */
  YYSYMBOL_declaration = 51,               /* declaration  */
  YYSYMBOL_init_declarator = 52,           /* init_declarator  */
  YYSYMBOL_initializer = 53,               /* initializer  */
  YYSYMBOL_expression = 54,                /* expression  */
  YYSYMBOL_constant_expression = 55,       /* constant_expression  */
  YYSYMBOL_logical_or_expressions = 56,    /* logical_or_expressions  */
  YYSYMBOL_logical_and_expressions = 57,   /* logical_and_expressions  */
  YYSYMBOL_equality_expression = 58,       /* equality_expression  */
  YYSYMBOL_relational_expression = 59,     /* relational_expression  */
  YYSYMBOL_additive_expression = 60,       /* additive_expression  */
  YYSYMBOL_multiplicative_expression = 61, /* multiplicative_expression  */
  YYSYMBOL_unary_expression = 62,          /* unary_expression  */
  YYSYMBOL_primary_expression = 63,        /* primary_expression  */
  YYSYMBOL_assignment_expression = 64,     /* assignment_expression  */
  YYSYMBOL_assignment_operator = 65,       /* assignment_operator  */
  YYSYMBOL_function_declaration = 66,      /* function_declaration  */
  YYSYMBOL_parameter_optional_list = 67,   /* parameter_optional_list  */
  YYSYMBOL_parameter_list = 68,            /* parameter_list  */
  YYSYMBOL_parameter_declaration = 69,     /* parameter_declaration  */
  YYSYMBOL_argument_list = 70,             /* argument_list  */
  YYSYMBOL_function_call = 71,             /* function_call  */
  YYSYMBOL_mostra_func_call = 72,          /* mostra_func_call  */
  YYSYMBOL_statements = 73,                /* statements  */
  YYSYMBOL_statement = 74,                 /* statement  */
  YYSYMBOL_import_statement = 75,          /* import_statement  */
  YYSYMBOL_single_import = 76,             /* single_import  */
  YYSYMBOL_expression_statement = 77,      /* expression_statement  */
  YYSYMBOL_compound_statement = 78,        /* compound_statement  */
  YYSYMBOL_selection_statement = 79,       /* selection_statement  */
  YYSYMBOL_else_then = 80,                 /* else_then  */
  YYSYMBOL_iteration_statement = 81,       /* iteration_statement  */
  YYSYMBOL_jump_statement = 82             /* jump_statement  */
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
#define YYFINAL  61
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   222

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  45
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  38
/* YYNRULES -- Number of rules.  */
#define YYNRULES  83
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  133

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   299


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
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,    75,    75,    78,    79,    80,    81,    84,    85,    86,
      87,    90,    94,    97,   100,   101,   105,   108,   109,   112,
     115,   116,   119,   120,   123,   124,   125,   128,   129,   130,
     131,   132,   135,   136,   137,   140,   141,   142,   145,   149,
     150,   151,   155,   156,   160,   163,   166,   167,   170,   171,
     174,   177,   178,   181,   182,   183,   186,   187,   190,   191,
     198,   199,   200,   201,   202,   203,   204,   205,   208,   211,
     214,   215,   218,   219,   222,   223,   226,   227,   230,   231,
     234,   235,   236,   237
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
  "\"end of file\"", "error", "\"invalid token\"", "IDENT", "STR_LIT",
  "MOSTRA", "INT_LIT", "FLOAT_LIT", "BOOL_LIT", "PLUS", "MINUS", "MUL",
  "DIV", "EQ", "NE", "LT", "LE", "GT", "GE", "AND", "OR", "ASSIGN",
  "LCURLY", "RCURLY", "COMMA", "SEMIC", "LBRAC", "RBRAC", "TYPE_INT",
  "TYPE_FLOAT", "TYPE_BOOL", "TYPE_VOID", "DIVOLVI", "DI", "STRUT",
  "NKUANTU", "SI", "SINON", "IMPRISTAN", "PARA", "CONTINUA", "DOT", "RPAR",
  "LPAR", "UMINUS", "$accept", "program", "type_specifier", "constant",
  "identifier", "declarator", "declaration", "init_declarator",
  "initializer", "expression", "constant_expression",
  "logical_or_expressions", "logical_and_expressions",
  "equality_expression", "relational_expression", "additive_expression",
  "multiplicative_expression", "unary_expression", "primary_expression",
  "assignment_expression", "assignment_operator", "function_declaration",
  "parameter_optional_list", "parameter_list", "parameter_declaration",
  "argument_list", "function_call", "mostra_func_call", "statements",
  "statement", "import_statement", "single_import", "expression_statement",
  "compound_statement", "selection_statement", "else_then",
  "iteration_statement", "jump_statement", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-87)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     123,   -87,   -87,   -26,   -87,   -87,   -87,     8,   -87,   -87,
     -87,   -87,   -87,   132,   179,   179,   179,    18,     9,    40,
     179,    28,    64,   -87,    30,   -87,    50,   -87,    83,    87,
       7,    54,    15,    38,   -87,    62,   -87,   -87,   -87,   -87,
     123,   -87,   -87,   -87,   -87,   -87,   -87,   -87,   164,   -87,
      82,   -87,    94,   107,    86,    86,   -87,   -87,   -87,   -87,
      91,   -87,   -87,   -17,   -87,   173,   -87,    73,    73,    73,
      73,    73,    73,    73,    73,    73,    73,    73,    73,   -87,
      73,   -87,   -87,   -87,   -19,   -87,   -87,   179,   -87,    97,
     -87,   179,    63,   -87,     3,   -87,    87,   -87,     7,    54,
      54,    15,    15,    15,    15,    38,    38,   -87,   -87,   -87,
     179,   -87,   116,    -4,   -87,   -87,    64,   100,   119,   -87,
     -87,   -87,   179,   -87,   -87,   -87,   -87,    86,    63,    86,
     -87,   -87,   -87
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,    11,    10,     0,     7,     8,     9,     0,    71,     3,
       4,     6,     5,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    40,    39,    66,     0,    42,    19,    20,
      22,    24,    27,    32,    35,    38,    17,    65,    18,    55,
       2,    59,    67,    60,    61,    62,    63,    64,     0,    73,
       0,    83,     0,     0,     0,     0,    69,    68,    80,    81,
       0,     1,    12,    14,    13,     0,    70,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    44,
       0,    58,    57,    52,     0,    72,    82,     0,    78,    74,
      41,     0,    47,    54,     0,    39,    21,    38,    23,    25,
      26,    28,    30,    29,    31,    33,    34,    36,    37,    43,
       0,    56,     0,     0,    15,    16,     0,     0,    46,    48,
      53,    51,     0,    76,    77,    75,    50,     0,     0,     0,
      45,    49,    79
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -87,   -87,   -86,   -87,   -14,    31,   -87,   -87,   -87,   -13,
     -87,   -87,    77,    78,    26,    27,    48,   -87,   121,    69,
     -87,   -87,   -87,   -87,    22,    95,   -87,   -87,   157,   -21,
     -87,   -87,   -87,   -45,    52,   -87,   -87,   -87
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,    21,    22,    23,    24,    63,    25,    64,   114,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      80,    37,   117,   118,   119,    84,    38,    39,    40,    41,
      42,    57,    43,    44,    45,   125,    46,    47
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      52,    53,    54,    55,    91,   110,   116,    60,    62,    88,
      89,     1,     2,     3,     4,     5,     6,    48,     7,    81,
      69,    70,    56,   111,    75,    76,    92,   110,    61,    81,
       7,    49,    16,     8,    58,    83,     9,    10,    11,    12,
      13,    14,   116,    15,    16,   120,    17,    18,    19,    77,
      78,    20,    83,    95,    95,    95,    95,    95,    95,    95,
      95,    95,    95,    95,    95,    59,    95,     1,   123,    71,
      72,    73,    74,    65,   112,    66,     1,     2,   115,     4,
       5,     6,   130,    79,   132,     1,     2,     3,     4,     5,
       6,     9,    10,    11,    12,    99,   100,   121,   101,   102,
     103,   104,    62,    67,     7,    85,    68,     8,     7,   129,
       9,    10,    11,    12,    13,    14,    20,    15,    16,    86,
      17,    18,    19,   105,   106,    20,     1,     2,     3,     4,
       5,     6,    87,    90,   113,     1,     2,     3,     4,     5,
       6,   122,   127,   128,    96,     7,    98,   126,     8,   109,
     131,     9,    10,    11,    12,    13,    14,    51,    15,    16,
      94,    17,    18,    19,    50,   124,    20,     1,     2,     3,
       4,     5,     6,     0,     0,    20,     1,     2,     3,     4,
       5,     6,     1,     2,     3,     4,     5,     6,    97,    97,
      97,    97,    97,    97,    97,    97,    97,    97,   107,   108,
       0,     0,     0,     0,     0,     0,    82,    20,     0,     0,
       0,     0,     0,     0,     0,    93,    20,     0,     0,     0,
       0,     0,    20
};

static const yytype_int16 yycheck[] =
{
      13,    14,    15,    16,    21,    24,    92,    20,    22,    54,
      55,     3,     4,     5,     6,     7,     8,    43,    22,    40,
      13,    14,     4,    42,     9,    10,    43,    24,     0,    50,
      22,    23,    36,    25,    25,    48,    28,    29,    30,    31,
      32,    33,   128,    35,    36,    42,    38,    39,    40,    11,
      12,    43,    65,    67,    68,    69,    70,    71,    72,    73,
      74,    75,    76,    77,    78,    25,    80,     3,   113,    15,
      16,    17,    18,    43,    87,    25,     3,     4,    91,     6,
       7,     8,   127,    21,   129,     3,     4,     5,     6,     7,
       8,    28,    29,    30,    31,    69,    70,   110,    71,    72,
      73,    74,   116,    20,    22,    23,    19,    25,    22,   122,
      28,    29,    30,    31,    32,    33,    43,    35,    36,    25,
      38,    39,    40,    75,    76,    43,     3,     4,     5,     6,
       7,     8,    25,    42,    37,     3,     4,     5,     6,     7,
       8,    25,    42,    24,    67,    22,    68,   116,    25,    80,
     128,    28,    29,    30,    31,    32,    33,    25,    35,    36,
      65,    38,    39,    40,     7,   113,    43,     3,     4,     5,
       6,     7,     8,    -1,    -1,    43,     3,     4,     5,     6,
       7,     8,     3,     4,     5,     6,     7,     8,    67,    68,
      69,    70,    71,    72,    73,    74,    75,    76,    77,    78,
      -1,    -1,    -1,    -1,    -1,    -1,    42,    43,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    42,    43,    -1,    -1,    -1,
      -1,    -1,    43
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     3,     4,     5,     6,     7,     8,    22,    25,    28,
      29,    30,    31,    32,    33,    35,    36,    38,    39,    40,
      43,    46,    47,    48,    49,    51,    54,    55,    56,    57,
      58,    59,    60,    61,    62,    63,    64,    66,    71,    72,
      73,    74,    75,    77,    78,    79,    81,    82,    43,    23,
      73,    25,    54,    54,    54,    54,     4,    76,    25,    25,
      54,     0,    49,    50,    52,    43,    25,    20,    19,    13,
      14,    15,    16,    17,    18,     9,    10,    11,    12,    21,
      65,    74,    42,    54,    70,    23,    25,    25,    78,    78,
      42,    21,    43,    42,    70,    49,    57,    63,    58,    59,
      59,    60,    60,    60,    60,    61,    61,    63,    63,    64,
      24,    42,    54,    37,    53,    54,    47,    67,    68,    69,
      42,    54,    25,    78,    79,    80,    50,    42,    24,    54,
      78,    69,    78
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    45,    46,    47,    47,    47,    47,    48,    48,    48,
      48,    49,    50,    51,    52,    52,    53,    54,    54,    55,
      56,    56,    57,    57,    58,    58,    58,    59,    59,    59,
      59,    59,    60,    60,    60,    61,    61,    61,    62,    63,
      63,    63,    64,    64,    65,    66,    67,    67,    68,    68,
      69,    70,    70,    71,    71,    71,    72,    72,    73,    73,
      74,    74,    74,    74,    74,    74,    74,    74,    75,    76,
      77,    77,    78,    78,    79,    79,    80,    80,    81,    81,
      82,    82,    82,    82
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     2,     1,     3,     1,     1,     1,     1,
       1,     3,     1,     3,     1,     3,     3,     1,     3,     3,
       3,     3,     1,     3,     3,     1,     3,     3,     1,     1,
       1,     3,     1,     3,     1,     6,     1,     0,     1,     3,
       2,     3,     1,     4,     3,     1,     4,     3,     2,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     2,     1,
       2,     1,     3,     2,     3,     5,     1,     1,     3,     7,
       2,     2,     3,     2
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
  case 2: /* program: statements  */
#line 75 "rules/parser.y"
                     { Program = (yyvsp[0].block); }
#line 1275 "parser.cc"
    break;

  case 6: /* type_specifier: TYPE_BOOL  */
#line 81 "rules/parser.y"
                           { (yyval.string) = new std::string("unsigned short"); }
#line 1281 "parser.cc"
    break;

  case 7: /* constant: INT_LIT  */
#line 84 "rules/parser.y"
                   { (yyval.expr) = new ast::LiteralExpr("int", *(yyvsp[0].integer)); (yyval.litexpr)->ActivateAutoCast(); }
#line 1287 "parser.cc"
    break;

  case 8: /* constant: FLOAT_LIT  */
#line 85 "rules/parser.y"
                     { (yyval.expr) = new ast::LiteralExpr("float", *(yyvsp[0].floatingpoint)); (yyval.litexpr)->ActivateAutoCast(); }
#line 1293 "parser.cc"
    break;

  case 9: /* constant: BOOL_LIT  */
#line 86 "rules/parser.y"
                    { (yyval.expr) = new ast::LiteralExpr("unsigned short", *(yyvsp[0].boolean)); (yyval.litexpr)->ActivateAutoCast(); }
#line 1299 "parser.cc"
    break;

  case 10: /* constant: STR_LIT  */
#line 87 "rules/parser.y"
                   { (yyval.expr) = new ast::LiteralExpr("char*", *(yyvsp[0].string)); (yyval.litexpr)->DeactivateAutoCast(); }
#line 1305 "parser.cc"
    break;

  case 13: /* declaration: type_specifier init_declarator  */
#line 97 "rules/parser.y"
                                             { (yyvsp[0].vardecl)->SetType(*(yyvsp[-1].string)); (yyval.sttmt) = (yyvsp[0].vardecl); }
#line 1311 "parser.cc"
    break;

  case 14: /* init_declarator: declarator  */
#line 100 "rules/parser.y"
                             { (yyval.vardecl) = new ast::VarDeclSttmt("void", *(yyvsp[0].string), nullptr); }
#line 1317 "parser.cc"
    break;

  case 15: /* init_declarator: declarator ASSIGN initializer  */
#line 101 "rules/parser.y"
                                                { (yyval.vardecl) = new ast::VarDeclSttmt("void", *(yyvsp[-2].string), (yyvsp[0].expr)); }
#line 1323 "parser.cc"
    break;

  case 21: /* logical_or_expressions: logical_or_expressions OR logical_and_expressions  */
#line 116 "rules/parser.y"
                                                                           { (yyval.expr) = new ast::BinExpr("||", (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 1329 "parser.cc"
    break;

  case 23: /* logical_and_expressions: logical_and_expressions AND equality_expression  */
#line 120 "rules/parser.y"
                                                                          { (yyval.expr) = new ast::BinExpr("&&", (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 1335 "parser.cc"
    break;

  case 25: /* equality_expression: equality_expression EQ relational_expression  */
#line 124 "rules/parser.y"
                                                                   { (yyval.expr) = new ast::BinExpr("==", (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 1341 "parser.cc"
    break;

  case 26: /* equality_expression: equality_expression NE relational_expression  */
#line 125 "rules/parser.y"
                                                                   { (yyval.expr) = new ast::BinExpr("!=", (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 1347 "parser.cc"
    break;

  case 28: /* relational_expression: relational_expression LT additive_expression  */
#line 129 "rules/parser.y"
                                                                     { (yyval.expr) = new ast::BinExpr("<", (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 1353 "parser.cc"
    break;

  case 29: /* relational_expression: relational_expression GT additive_expression  */
#line 130 "rules/parser.y"
                                                                     { (yyval.expr) = new ast::BinExpr(">", (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 1359 "parser.cc"
    break;

  case 30: /* relational_expression: relational_expression LE additive_expression  */
#line 131 "rules/parser.y"
                                                                     { (yyval.expr) = new ast::BinExpr("<=", (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 1365 "parser.cc"
    break;

  case 31: /* relational_expression: relational_expression GE additive_expression  */
#line 132 "rules/parser.y"
                                                                     { (yyval.expr) = new ast::BinExpr(">=", (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 1371 "parser.cc"
    break;

  case 33: /* additive_expression: additive_expression PLUS multiplicative_expression  */
#line 136 "rules/parser.y"
                                                                         { (yyval.expr) = new ast::BinExpr("+", (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 1377 "parser.cc"
    break;

  case 34: /* additive_expression: additive_expression MINUS multiplicative_expression  */
#line 137 "rules/parser.y"
                                                                          { (yyval.expr) = new ast::BinExpr("-", (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 1383 "parser.cc"
    break;

  case 36: /* multiplicative_expression: multiplicative_expression MUL primary_expression  */
#line 141 "rules/parser.y"
                                                                             { (yyval.expr) = new ast::BinExpr("*", (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 1389 "parser.cc"
    break;

  case 37: /* multiplicative_expression: multiplicative_expression DIV primary_expression  */
#line 142 "rules/parser.y"
                                                                             { (yyval.expr) = new ast::BinExpr("/", (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 1395 "parser.cc"
    break;

  case 39: /* primary_expression: identifier  */
#line 149 "rules/parser.y"
                                { (yyval.expr) = new ast::IdentExpr(*(yyvsp[0].string)); }
#line 1401 "parser.cc"
    break;

  case 41: /* primary_expression: LPAR expression RPAR  */
#line 151 "rules/parser.y"
                                          { (yyval.expr) = new ast::ParExpr((yyvsp[-1].expr)); }
#line 1407 "parser.cc"
    break;

  case 43: /* assignment_expression: primary_expression assignment_operator assignment_expression  */
#line 156 "rules/parser.y"
                                                                                     { (yyval.expr) = new ast::AssignExpr(*(yyvsp[-1].string), (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 1413 "parser.cc"
    break;

  case 44: /* assignment_operator: ASSIGN  */
#line 160 "rules/parser.y"
                             { (yyval.string) = new std::string("=", 2); }
#line 1419 "parser.cc"
    break;

  case 45: /* function_declaration: type_specifier declarator LPAR parameter_optional_list RPAR compound_statement  */
#line 163 "rules/parser.y"
                                                                                                      { (yyval.sttmt) = new ast::FuncDeclSttmt(*(yyvsp[-5].string), *(yyvsp[-4].string), (yyvsp[-2].params), (yyvsp[0].block)); }
#line 1425 "parser.cc"
    break;

  case 47: /* parameter_optional_list: %empty  */
#line 167 "rules/parser.y"
                                 { (yyval.params) = new ast::FuncArgs(); }
#line 1431 "parser.cc"
    break;

  case 48: /* parameter_list: parameter_declaration  */
#line 170 "rules/parser.y"
                                       { (yyval.params) = new ast::FuncArgs(); (yyval.params)->AddArg((yyvsp[0].vardecl)); }
#line 1437 "parser.cc"
    break;

  case 49: /* parameter_list: parameter_list COMMA parameter_declaration  */
#line 171 "rules/parser.y"
                                                            { { (yyvsp[-2].params)->AddArg((yyvsp[0].vardecl)); } }
#line 1443 "parser.cc"
    break;

  case 50: /* parameter_declaration: type_specifier declarator  */
#line 174 "rules/parser.y"
                                                  { (yyval.vardecl) = new ast::VarDeclSttmt(*(yyvsp[-1].string), *(yyvsp[0].string), nullptr); }
#line 1449 "parser.cc"
    break;

  case 51: /* argument_list: argument_list COMMA expression  */
#line 177 "rules/parser.y"
                                               { (yyvsp[-2].args)->AddArg((yyvsp[0].expr)); }
#line 1455 "parser.cc"
    break;

  case 52: /* argument_list: expression  */
#line 178 "rules/parser.y"
                           { (yyval.args) = new ast::FuncCallArgs(); (yyval.args)->AddArg((yyvsp[0].expr));  }
#line 1461 "parser.cc"
    break;

  case 53: /* function_call: identifier LPAR argument_list RPAR  */
#line 181 "rules/parser.y"
                                                   { (yyval.expr) = new ast::FunCallExpr(*(yyvsp[-3].string), (yyvsp[-1].args)); }
#line 1467 "parser.cc"
    break;

  case 54: /* function_call: identifier LPAR RPAR  */
#line 182 "rules/parser.y"
                                     { (yyval.expr) = new ast::FunCallExpr(*(yyvsp[-2].string), nullptr); }
#line 1473 "parser.cc"
    break;

  case 56: /* mostra_func_call: MOSTRA LPAR argument_list RPAR  */
#line 186 "rules/parser.y"
                                                  { (yyval.expr) = new ast::MostraFunCallExpr((yyvsp[-1].args)); }
#line 1479 "parser.cc"
    break;

  case 57: /* mostra_func_call: MOSTRA LPAR RPAR  */
#line 187 "rules/parser.y"
                                    { (yyval.expr) = new ast::MostraFunCallExpr(nullptr); }
#line 1485 "parser.cc"
    break;

  case 58: /* statements: statements statement  */
#line 190 "rules/parser.y"
                                  { (yyvsp[-1].block)->AddSttmt((yyvsp[0].sttmt)); }
#line 1491 "parser.cc"
    break;

  case 59: /* statements: statement  */
#line 191 "rules/parser.y"
                       { (yyval.block) = new ast::BlockSttmt(); (yyval.block)->AddSttmt((yyvsp[0].sttmt)); }
#line 1497 "parser.cc"
    break;

  case 61: /* statement: compound_statement  */
#line 199 "rules/parser.y"
                               { (yyval.sttmt) = (yyvsp[0].block); }
#line 1503 "parser.cc"
    break;

  case 67: /* statement: import_statement  */
#line 205 "rules/parser.y"
                             { (yyval.sttmt) = (yyvsp[0].sttmt); }
#line 1509 "parser.cc"
    break;

  case 68: /* import_statement: IMPRISTAN single_import  */
#line 208 "rules/parser.y"
                                           { (yyval.sttmt) = new ast::ImportSttmt(*(yyvsp[0].string)); }
#line 1515 "parser.cc"
    break;

  case 70: /* expression_statement: expression SEMIC  */
#line 214 "rules/parser.y"
                                        { (yyval.sttmt) = new ast::ExprSttmt((yyvsp[-1].expr)); }
#line 1521 "parser.cc"
    break;

  case 71: /* expression_statement: SEMIC  */
#line 215 "rules/parser.y"
                             { (yyval.sttmt) = new ast::ExprSttmt(nullptr); }
#line 1527 "parser.cc"
    break;

  case 72: /* compound_statement: LCURLY statements RCURLY  */
#line 218 "rules/parser.y"
                                              { (yyval.block) = (yyvsp[-1].block); (yyval.block)->UseBrackets(); }
#line 1533 "parser.cc"
    break;

  case 73: /* compound_statement: LCURLY RCURLY  */
#line 219 "rules/parser.y"
                                   { (yyval.block) = new ast::BlockSttmt(); (yyval.block)->UseBrackets(); }
#line 1539 "parser.cc"
    break;

  case 74: /* selection_statement: SI expression compound_statement  */
#line 222 "rules/parser.y"
                                                       { (yyval.sttmt) = new ast::IfSttmt((yyvsp[-1].expr), (yyvsp[0].block), nullptr); }
#line 1545 "parser.cc"
    break;

  case 75: /* selection_statement: SI expression compound_statement SINON else_then  */
#line 223 "rules/parser.y"
                                                                       { (yyval.sttmt) = new ast::IfSttmt((yyvsp[-3].expr), (yyvsp[-2].block), (yyvsp[0].block)); }
#line 1551 "parser.cc"
    break;

  case 77: /* else_then: selection_statement  */
#line 227 "rules/parser.y"
                                { (yyval.block) = new ast::BlockSttmt(); (yyval.block)->AddSttmt((yyvsp[0].sttmt)); }
#line 1557 "parser.cc"
    break;

  case 78: /* iteration_statement: NKUANTU expression compound_statement  */
#line 230 "rules/parser.y"
                                                            { (yyval.sttmt) = new ast::WhileSttmt((yyvsp[-1].expr), (yyvsp[0].block)); }
#line 1563 "parser.cc"
    break;

  case 79: /* iteration_statement: DI expression SEMIC expression SEMIC expression compound_statement  */
#line 231 "rules/parser.y"
                                                                                         { (yyval.sttmt) = new ast::ForSttmt((yyvsp[-5].expr), (yyvsp[-3].expr), (yyvsp[-1].expr), (yyvsp[0].block)); }
#line 1569 "parser.cc"
    break;

  case 80: /* jump_statement: PARA SEMIC  */
#line 234 "rules/parser.y"
                            { (yyval.sttmt) = new ast::JumpSttmt("break"); }
#line 1575 "parser.cc"
    break;

  case 81: /* jump_statement: CONTINUA SEMIC  */
#line 235 "rules/parser.y"
                                { (yyval.sttmt) = new ast::JumpSttmt("continue"); }
#line 1581 "parser.cc"
    break;

  case 82: /* jump_statement: DIVOLVI expression SEMIC  */
#line 236 "rules/parser.y"
                                          { (yyval.sttmt) = new ast::ReturnSttmt((yyvsp[-1].expr)); }
#line 1587 "parser.cc"
    break;

  case 83: /* jump_statement: DIVOLVI SEMIC  */
#line 237 "rules/parser.y"
                               { (yyval.sttmt) = new ast::ReturnSttmt(nullptr); }
#line 1593 "parser.cc"
    break;


#line 1597 "parser.cc"

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

#line 239 "rules/parser.y"


void yyerror(const char* err) {
    creol::cli::PrintErr(err, 1);
}

