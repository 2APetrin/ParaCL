// A Bison parser, made by GNU Bison 3.8.2.

// Skeleton implementation for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2015, 2018-2021 Free Software Foundation, Inc.

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

// As a special exception, you may create a larger work that contains
// part or all of the Bison parser skeleton and distribute that work
// under terms of your choice, so long as that work isn't itself a
// parser generator using the skeleton or a modified version thereof
// as a parser skeleton.  Alternatively, if you modify or redistribute
// the parser skeleton itself, you may (at your option) remove this
// special exception, which will cause the skeleton and the resulting
// Bison output files to be licensed under the GNU General Public
// License without this special exception.

// This special exception was added by the Free Software Foundation in
// version 2.2 of Bison.

// DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
// especially those whose name start with YY_ or yy_.  They are
// private implementation details that can be changed or removed.





#include "grammar.tab.hh"




#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> // FIXME: INFRINGES ON USER NAME SPACE.
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif


// Whether we are compiled with exception support.
#ifndef YY_EXCEPTIONS
# if defined __GNUC__ && !defined __EXCEPTIONS
#  define YY_EXCEPTIONS 0
# else
#  define YY_EXCEPTIONS 1
# endif
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K].location)
/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

# ifndef YYLLOC_DEFAULT
#  define YYLLOC_DEFAULT(Current, Rhs, N)                               \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).begin  = YYRHSLOC (Rhs, 1).begin;                   \
          (Current).end    = YYRHSLOC (Rhs, N).end;                     \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).begin = (Current).end = YYRHSLOC (Rhs, 0).end;      \
        }                                                               \
    while (false)
# endif


// Enable debugging if requested.
#if YYDEBUG

// A pseudo ostream that takes yydebug_ into account.
# define YYCDEBUG if (yydebug_) (*yycdebug_)

# define YY_SYMBOL_PRINT(Title, Symbol)         \
  do {                                          \
    if (yydebug_)                               \
    {                                           \
      *yycdebug_ << Title << ' ';               \
      yy_print_ (*yycdebug_, Symbol);           \
      *yycdebug_ << '\n';                       \
    }                                           \
  } while (false)

# define YY_REDUCE_PRINT(Rule)          \
  do {                                  \
    if (yydebug_)                       \
      yy_reduce_print_ (Rule);          \
  } while (false)

# define YY_STACK_PRINT()               \
  do {                                  \
    if (yydebug_)                       \
      yy_stack_print_ ();                \
  } while (false)

#else // !YYDEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YY_USE (Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void> (0)
# define YY_STACK_PRINT()                static_cast<void> (0)

#endif // !YYDEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyla.clear ())

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)

namespace yy {
#line 136 "/home/tony/code/cxx/ParaCL/build/parser.cc"

  /// Build a parser object.
  parser::parser (yy::driver* drv_yyarg)
#if YYDEBUG
    : yydebug_ (false),
      yycdebug_ (&std::cerr),
#else
    :
#endif
      yy_lac_established_ (false),
      drv (drv_yyarg)
  {}

  parser::~parser ()
  {}

  parser::syntax_error::~syntax_error () YY_NOEXCEPT YY_NOTHROW
  {}

  /*---------.
  | symbol.  |
  `---------*/



  // by_state.
  parser::by_state::by_state () YY_NOEXCEPT
    : state (empty_state)
  {}

  parser::by_state::by_state (const by_state& that) YY_NOEXCEPT
    : state (that.state)
  {}

  void
  parser::by_state::clear () YY_NOEXCEPT
  {
    state = empty_state;
  }

  void
  parser::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

  parser::by_state::by_state (state_type s) YY_NOEXCEPT
    : state (s)
  {}

  parser::symbol_kind_type
  parser::by_state::kind () const YY_NOEXCEPT
  {
    if (state == empty_state)
      return symbol_kind::S_YYEMPTY;
    else
      return YY_CAST (symbol_kind_type, yystos_[+state]);
  }

  parser::stack_symbol_type::stack_symbol_type ()
  {}

  parser::stack_symbol_type::stack_symbol_type (YY_RVREF (stack_symbol_type) that)
    : super_type (YY_MOVE (that.state), YY_MOVE (that.location))
  {
    switch (that.kind ())
    {
      case symbol_kind::S_NUMBER: // NUMBER
        value.YY_MOVE_OR_COPY< int > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_scope: // scope
      case symbol_kind::S_op: // op
      case symbol_kind::S_scope_br: // scope_br
      case symbol_kind::S_scope_br_start: // scope_br_start
      case symbol_kind::S_expr: // expr
      case symbol_kind::S_primary_expr: // primary_expr
      case symbol_kind::S_if: // if
      case symbol_kind::S_if_start: // if_start
      case symbol_kind::S_while_start: // while_start
        value.YY_MOVE_OR_COPY< ptd::i_node* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_lang_func: // lang_func
        value.YY_MOVE_OR_COPY< ptd::i_one_child* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_while: // while
        value.YY_MOVE_OR_COPY< ptd::i_two_child* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_else_start: // else_start
        value.YY_MOVE_OR_COPY< ptd::scope* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_else: // else
        value.YY_MOVE_OR_COPY< std::pair<ptd::scope*, ptd::scope*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_ID: // ID
        value.YY_MOVE_OR_COPY< std::string > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

#if 201103L <= YY_CPLUSPLUS
    // that is emptied.
    that.state = empty_state;
#endif
  }

  parser::stack_symbol_type::stack_symbol_type (state_type s, YY_MOVE_REF (symbol_type) that)
    : super_type (s, YY_MOVE (that.location))
  {
    switch (that.kind ())
    {
      case symbol_kind::S_NUMBER: // NUMBER
        value.move< int > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_scope: // scope
      case symbol_kind::S_op: // op
      case symbol_kind::S_scope_br: // scope_br
      case symbol_kind::S_scope_br_start: // scope_br_start
      case symbol_kind::S_expr: // expr
      case symbol_kind::S_primary_expr: // primary_expr
      case symbol_kind::S_if: // if
      case symbol_kind::S_if_start: // if_start
      case symbol_kind::S_while_start: // while_start
        value.move< ptd::i_node* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_lang_func: // lang_func
        value.move< ptd::i_one_child* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_while: // while
        value.move< ptd::i_two_child* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_else_start: // else_start
        value.move< ptd::scope* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_else: // else
        value.move< std::pair<ptd::scope*, ptd::scope*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_ID: // ID
        value.move< std::string > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

    // that is emptied.
    that.kind_ = symbol_kind::S_YYEMPTY;
  }

#if YY_CPLUSPLUS < 201103L
  parser::stack_symbol_type&
  parser::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
    switch (that.kind ())
    {
      case symbol_kind::S_NUMBER: // NUMBER
        value.copy< int > (that.value);
        break;

      case symbol_kind::S_scope: // scope
      case symbol_kind::S_op: // op
      case symbol_kind::S_scope_br: // scope_br
      case symbol_kind::S_scope_br_start: // scope_br_start
      case symbol_kind::S_expr: // expr
      case symbol_kind::S_primary_expr: // primary_expr
      case symbol_kind::S_if: // if
      case symbol_kind::S_if_start: // if_start
      case symbol_kind::S_while_start: // while_start
        value.copy< ptd::i_node* > (that.value);
        break;

      case symbol_kind::S_lang_func: // lang_func
        value.copy< ptd::i_one_child* > (that.value);
        break;

      case symbol_kind::S_while: // while
        value.copy< ptd::i_two_child* > (that.value);
        break;

      case symbol_kind::S_else_start: // else_start
        value.copy< ptd::scope* > (that.value);
        break;

      case symbol_kind::S_else: // else
        value.copy< std::pair<ptd::scope*, ptd::scope*> > (that.value);
        break;

      case symbol_kind::S_ID: // ID
        value.copy< std::string > (that.value);
        break;

      default:
        break;
    }

    location = that.location;
    return *this;
  }

  parser::stack_symbol_type&
  parser::stack_symbol_type::operator= (stack_symbol_type& that)
  {
    state = that.state;
    switch (that.kind ())
    {
      case symbol_kind::S_NUMBER: // NUMBER
        value.move< int > (that.value);
        break;

      case symbol_kind::S_scope: // scope
      case symbol_kind::S_op: // op
      case symbol_kind::S_scope_br: // scope_br
      case symbol_kind::S_scope_br_start: // scope_br_start
      case symbol_kind::S_expr: // expr
      case symbol_kind::S_primary_expr: // primary_expr
      case symbol_kind::S_if: // if
      case symbol_kind::S_if_start: // if_start
      case symbol_kind::S_while_start: // while_start
        value.move< ptd::i_node* > (that.value);
        break;

      case symbol_kind::S_lang_func: // lang_func
        value.move< ptd::i_one_child* > (that.value);
        break;

      case symbol_kind::S_while: // while
        value.move< ptd::i_two_child* > (that.value);
        break;

      case symbol_kind::S_else_start: // else_start
        value.move< ptd::scope* > (that.value);
        break;

      case symbol_kind::S_else: // else
        value.move< std::pair<ptd::scope*, ptd::scope*> > (that.value);
        break;

      case symbol_kind::S_ID: // ID
        value.move< std::string > (that.value);
        break;

      default:
        break;
    }

    location = that.location;
    // that is emptied.
    that.state = empty_state;
    return *this;
  }
#endif

  template <typename Base>
  void
  parser::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);
  }

#if YYDEBUG
  template <typename Base>
  void
  parser::yy_print_ (std::ostream& yyo, const basic_symbol<Base>& yysym) const
  {
    std::ostream& yyoutput = yyo;
    YY_USE (yyoutput);
    if (yysym.empty ())
      yyo << "empty symbol";
    else
      {
        symbol_kind_type yykind = yysym.kind ();
        yyo << (yykind < YYNTOKENS ? "token" : "nterm")
            << ' ' << yysym.name () << " ("
            << yysym.location << ": ";
        YY_USE (yykind);
        yyo << ')';
      }
  }
#endif

  void
  parser::yypush_ (const char* m, YY_MOVE_REF (stack_symbol_type) sym)
  {
    if (m)
      YY_SYMBOL_PRINT (m, sym);
    yystack_.push (YY_MOVE (sym));
  }

  void
  parser::yypush_ (const char* m, state_type s, YY_MOVE_REF (symbol_type) sym)
  {
#if 201103L <= YY_CPLUSPLUS
    yypush_ (m, stack_symbol_type (s, std::move (sym)));
#else
    stack_symbol_type ss (s, sym);
    yypush_ (m, ss);
#endif
  }

  void
  parser::yypop_ (int n) YY_NOEXCEPT
  {
    yystack_.pop (n);
  }

#if YYDEBUG
  std::ostream&
  parser::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  parser::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  parser::debug_level_type
  parser::debug_level () const
  {
    return yydebug_;
  }

  void
  parser::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif // YYDEBUG

  parser::state_type
  parser::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - YYNTOKENS] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - YYNTOKENS];
  }

  bool
  parser::yy_pact_value_is_default_ (int yyvalue) YY_NOEXCEPT
  {
    return yyvalue == yypact_ninf_;
  }

  bool
  parser::yy_table_value_is_error_ (int yyvalue) YY_NOEXCEPT
  {
    return yyvalue == yytable_ninf_;
  }

  int
  parser::operator() ()
  {
    return parse ();
  }

  int
  parser::parse ()
  {
    int yyn;
    /// Length of the RHS of the rule being reduced.
    int yylen = 0;

    // Error handling.
    int yynerrs_ = 0;
    int yyerrstatus_ = 0;

    /// The lookahead symbol.
    symbol_type yyla;

    /// The locations where the error started and ended.
    stack_symbol_type yyerror_range[3];

    /// The return value of parse ().
    int yyresult;

    // Discard the LAC context in case there still is one left from a
    // previous invocation.
    yy_lac_discard_ ("init");

#if YY_EXCEPTIONS
    try
#endif // YY_EXCEPTIONS
      {
    YYCDEBUG << "Starting parse\n";


    /* Initialize the stack.  The initial state will be set in
       yynewstate, since the latter expects the semantical and the
       location values to have been already stored, initialize these
       stacks with a primary value.  */
    yystack_.clear ();
    yypush_ (YY_NULLPTR, 0, YY_MOVE (yyla));

  /*-----------------------------------------------.
  | yynewstate -- push a new symbol on the stack.  |
  `-----------------------------------------------*/
  yynewstate:
    YYCDEBUG << "Entering state " << int (yystack_[0].state) << '\n';
    YY_STACK_PRINT ();

    // Accept?
    if (yystack_[0].state == yyfinal_)
      YYACCEPT;

    goto yybackup;


  /*-----------.
  | yybackup.  |
  `-----------*/
  yybackup:
    // Try to take a decision without lookahead.
    yyn = yypact_[+yystack_[0].state];
    if (yy_pact_value_is_default_ (yyn))
      goto yydefault;

    // Read a lookahead token.
    if (yyla.empty ())
      {
        YYCDEBUG << "Reading a token\n";
#if YY_EXCEPTIONS
        try
#endif // YY_EXCEPTIONS
          {
            symbol_type yylookahead (yylex (drv));
            yyla.move (yylookahead);
          }
#if YY_EXCEPTIONS
        catch (const syntax_error& yyexc)
          {
            YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
            error (yyexc);
            goto yyerrlab1;
          }
#endif // YY_EXCEPTIONS
      }
    YY_SYMBOL_PRINT ("Next token is", yyla);

    if (yyla.kind () == symbol_kind::S_YYerror)
    {
      // The scanner already issued an error message, process directly
      // to error recovery.  But do not keep the error token as
      // lookahead, it is too special and may lead us to an endless
      // loop in error recovery. */
      yyla.kind_ = symbol_kind::S_YYUNDEF;
      goto yyerrlab1;
    }

    /* If the proper action on seeing token YYLA.TYPE is to reduce or
       to detect an error, take that action.  */
    yyn += yyla.kind ();
    if (yyn < 0 || yylast_ < yyn || yycheck_[yyn] != yyla.kind ())
      {
        if (!yy_lac_establish_ (yyla.kind ()))
          goto yyerrlab;
        goto yydefault;
      }

    // Reduce or error.
    yyn = yytable_[yyn];
    if (yyn <= 0)
      {
        if (yy_table_value_is_error_ (yyn))
          goto yyerrlab;
        if (!yy_lac_establish_ (yyla.kind ()))
          goto yyerrlab;

        yyn = -yyn;
        goto yyreduce;
      }

    // Count tokens shifted since error; after three, turn off error status.
    if (yyerrstatus_)
      --yyerrstatus_;

    // Shift the lookahead token.
    yypush_ ("Shifting", state_type (yyn), YY_MOVE (yyla));
    yy_lac_discard_ ("shift");
    goto yynewstate;


  /*-----------------------------------------------------------.
  | yydefault -- do the default action for the current state.  |
  `-----------------------------------------------------------*/
  yydefault:
    yyn = yydefact_[+yystack_[0].state];
    if (yyn == 0)
      goto yyerrlab;
    goto yyreduce;


  /*-----------------------------.
  | yyreduce -- do a reduction.  |
  `-----------------------------*/
  yyreduce:
    yylen = yyr2_[yyn];
    {
      stack_symbol_type yylhs;
      yylhs.state = yy_lr_goto_state_ (yystack_[yylen].state, yyr1_[yyn]);
      /* Variants are always initialized to an empty instance of the
         correct type. The default '$$ = $1' action is NOT applied
         when using variants.  */
      switch (yyr1_[yyn])
    {
      case symbol_kind::S_NUMBER: // NUMBER
        yylhs.value.emplace< int > ();
        break;

      case symbol_kind::S_scope: // scope
      case symbol_kind::S_op: // op
      case symbol_kind::S_scope_br: // scope_br
      case symbol_kind::S_scope_br_start: // scope_br_start
      case symbol_kind::S_expr: // expr
      case symbol_kind::S_primary_expr: // primary_expr
      case symbol_kind::S_if: // if
      case symbol_kind::S_if_start: // if_start
      case symbol_kind::S_while_start: // while_start
        yylhs.value.emplace< ptd::i_node* > ();
        break;

      case symbol_kind::S_lang_func: // lang_func
        yylhs.value.emplace< ptd::i_one_child* > ();
        break;

      case symbol_kind::S_while: // while
        yylhs.value.emplace< ptd::i_two_child* > ();
        break;

      case symbol_kind::S_else_start: // else_start
        yylhs.value.emplace< ptd::scope* > ();
        break;

      case symbol_kind::S_else: // else
        yylhs.value.emplace< std::pair<ptd::scope*, ptd::scope*> > ();
        break;

      case symbol_kind::S_ID: // ID
        yylhs.value.emplace< std::string > ();
        break;

      default:
        break;
    }


      // Default location.
      {
        stack_type::slice range (yystack_, yylen);
        YYLLOC_DEFAULT (yylhs.location, range, yylen);
        yyerror_range[1].location = yylhs.location;
      }

      // Perform the reduction.
      YY_REDUCE_PRINT (yyn);
#if YY_EXCEPTIONS
      try
#endif // YY_EXCEPTIONS
        {
          switch (yyn)
            {
  case 2: // program: scope
#line 114 "/home/tony/code/cxx/ParaCL/parser/grammar.y"
               {
#ifdef DUMP
    drv->tree.graphviz_dump();
#endif
    drv->tree.execute_tree();
}
#line 726 "/home/tony/code/cxx/ParaCL/build/parser.cc"
    break;

  case 3: // scope: op scope
#line 122 "/home/tony/code/cxx/ParaCL/parser/grammar.y"
                { }
#line 732 "/home/tony/code/cxx/ParaCL/build/parser.cc"
    break;

  case 4: // scope: %empty
#line 123 "/home/tony/code/cxx/ParaCL/parser/grammar.y"
                { }
#line 738 "/home/tony/code/cxx/ParaCL/build/parser.cc"
    break;

  case 5: // op: expr ";"
#line 126 "/home/tony/code/cxx/ParaCL/parser/grammar.y"
                  { yylhs.value.as < ptd::i_node* > () = yystack_[1].value.as < ptd::i_node* > ();              drv->curr_scope_->add_child(yylhs.value.as < ptd::i_node* > ()); }
#line 744 "/home/tony/code/cxx/ParaCL/build/parser.cc"
    break;

  case 6: // op: while
#line 127 "/home/tony/code/cxx/ParaCL/parser/grammar.y"
                  { yylhs.value.as < ptd::i_node* > () = yystack_[0].value.as < ptd::i_two_child* > ();              drv->curr_scope_->add_child(yylhs.value.as < ptd::i_node* > ()); }
#line 750 "/home/tony/code/cxx/ParaCL/build/parser.cc"
    break;

  case 7: // op: if
#line 128 "/home/tony/code/cxx/ParaCL/parser/grammar.y"
                  { yylhs.value.as < ptd::i_node* > () = yystack_[0].value.as < ptd::i_node* > ();              drv->curr_scope_->add_child(yylhs.value.as < ptd::i_node* > ()); }
#line 756 "/home/tony/code/cxx/ParaCL/build/parser.cc"
    break;

  case 8: // op: lang_func
#line 129 "/home/tony/code/cxx/ParaCL/parser/grammar.y"
                  { yylhs.value.as < ptd::i_node* > () = yystack_[0].value.as < ptd::i_one_child* > ();              drv->curr_scope_->add_child(yylhs.value.as < ptd::i_node* > ()); }
#line 762 "/home/tony/code/cxx/ParaCL/build/parser.cc"
    break;

  case 9: // op: scope_br
#line 130 "/home/tony/code/cxx/ParaCL/parser/grammar.y"
                  { yylhs.value.as < ptd::i_node* > () = yystack_[0].value.as < ptd::i_node* > ();              drv->curr_scope_->add_child(yylhs.value.as < ptd::i_node* > ()); }
#line 768 "/home/tony/code/cxx/ParaCL/build/parser.cc"
    break;

  case 10: // op: ";"
#line 131 "/home/tony/code/cxx/ParaCL/parser/grammar.y"
                  { yylhs.value.as < ptd::i_node* > () = drv->make_nop(); drv->curr_scope_->add_child(yylhs.value.as < ptd::i_node* > ()); }
#line 774 "/home/tony/code/cxx/ParaCL/build/parser.cc"
    break;

  case 11: // scope_br: scope_br_start scope "}"
#line 134 "/home/tony/code/cxx/ParaCL/parser/grammar.y"
                                   { yylhs.value.as < ptd::i_node* > () = yystack_[2].value.as < ptd::i_node* > (); drv->reset_scope(); }
#line 780 "/home/tony/code/cxx/ParaCL/build/parser.cc"
    break;

  case 12: // scope_br_start: "{"
#line 136 "/home/tony/code/cxx/ParaCL/parser/grammar.y"
                    { drv->new_scope(); yylhs.value.as < ptd::i_node* > () = drv->curr_scope_; }
#line 786 "/home/tony/code/cxx/ParaCL/build/parser.cc"
    break;

  case 13: // expr: primary_expr
#line 138 "/home/tony/code/cxx/ParaCL/parser/grammar.y"
      { yylhs.value.as < ptd::i_node* > () = yystack_[0].value.as < ptd::i_node* > (); }
#line 792 "/home/tony/code/cxx/ParaCL/build/parser.cc"
    break;

  case 14: // expr: expr "+" expr
#line 139 "/home/tony/code/cxx/ParaCL/parser/grammar.y"
                    { yylhs.value.as < ptd::i_node* > () = drv->make_d_op<ptop::ADD>(yystack_[2].value.as < ptd::i_node* > (), yystack_[0].value.as < ptd::i_node* > ()); }
#line 798 "/home/tony/code/cxx/ParaCL/build/parser.cc"
    break;

  case 15: // expr: expr "-" expr
#line 140 "/home/tony/code/cxx/ParaCL/parser/grammar.y"
                    { yylhs.value.as < ptd::i_node* > () = drv->make_d_op<ptop::SUB>(yystack_[2].value.as < ptd::i_node* > (), yystack_[0].value.as < ptd::i_node* > ()); }
#line 804 "/home/tony/code/cxx/ParaCL/build/parser.cc"
    break;

  case 16: // expr: expr "*" expr
#line 141 "/home/tony/code/cxx/ParaCL/parser/grammar.y"
                    { yylhs.value.as < ptd::i_node* > () = drv->make_d_op<ptop::MUL>(yystack_[2].value.as < ptd::i_node* > (), yystack_[0].value.as < ptd::i_node* > ()); }
#line 810 "/home/tony/code/cxx/ParaCL/build/parser.cc"
    break;

  case 17: // expr: expr "/" expr
#line 142 "/home/tony/code/cxx/ParaCL/parser/grammar.y"
                    { yylhs.value.as < ptd::i_node* > () = drv->make_d_op<ptop::DIV>(yystack_[2].value.as < ptd::i_node* > (), yystack_[0].value.as < ptd::i_node* > ()); }
#line 816 "/home/tony/code/cxx/ParaCL/build/parser.cc"
    break;

  case 18: // expr: expr "%" expr
#line 143 "/home/tony/code/cxx/ParaCL/parser/grammar.y"
                    { yylhs.value.as < ptd::i_node* > () = drv->make_d_op<ptop::MOD>(yystack_[2].value.as < ptd::i_node* > (), yystack_[0].value.as < ptd::i_node* > ()); }
#line 822 "/home/tony/code/cxx/ParaCL/build/parser.cc"
    break;

  case 19: // expr: expr ">" expr
#line 144 "/home/tony/code/cxx/ParaCL/parser/grammar.y"
                    { yylhs.value.as < ptd::i_node* > () = drv->make_d_op<ptop::GR> (yystack_[2].value.as < ptd::i_node* > (), yystack_[0].value.as < ptd::i_node* > ()); }
#line 828 "/home/tony/code/cxx/ParaCL/build/parser.cc"
    break;

  case 20: // expr: expr ">=" expr
#line 145 "/home/tony/code/cxx/ParaCL/parser/grammar.y"
                    { yylhs.value.as < ptd::i_node* > () = drv->make_d_op<ptop::GRE>(yystack_[2].value.as < ptd::i_node* > (), yystack_[0].value.as < ptd::i_node* > ()); }
#line 834 "/home/tony/code/cxx/ParaCL/build/parser.cc"
    break;

  case 21: // expr: expr "<" expr
#line 146 "/home/tony/code/cxx/ParaCL/parser/grammar.y"
                    { yylhs.value.as < ptd::i_node* > () = drv->make_d_op<ptop::BL> (yystack_[2].value.as < ptd::i_node* > (), yystack_[0].value.as < ptd::i_node* > ()); }
#line 840 "/home/tony/code/cxx/ParaCL/build/parser.cc"
    break;

  case 22: // expr: expr "<=" expr
#line 147 "/home/tony/code/cxx/ParaCL/parser/grammar.y"
                    { yylhs.value.as < ptd::i_node* > () = drv->make_d_op<ptop::BLE>(yystack_[2].value.as < ptd::i_node* > (), yystack_[0].value.as < ptd::i_node* > ()); }
#line 846 "/home/tony/code/cxx/ParaCL/build/parser.cc"
    break;

  case 23: // expr: expr "==" expr
#line 148 "/home/tony/code/cxx/ParaCL/parser/grammar.y"
                    { yylhs.value.as < ptd::i_node* > () = drv->make_d_op<ptop::EQ> (yystack_[2].value.as < ptd::i_node* > (), yystack_[0].value.as < ptd::i_node* > ()); }
#line 852 "/home/tony/code/cxx/ParaCL/build/parser.cc"
    break;

  case 24: // expr: expr "!=" expr
#line 149 "/home/tony/code/cxx/ParaCL/parser/grammar.y"
                    { yylhs.value.as < ptd::i_node* > () = drv->make_d_op<ptop::NEQ>(yystack_[2].value.as < ptd::i_node* > (), yystack_[0].value.as < ptd::i_node* > ()); }
#line 858 "/home/tony/code/cxx/ParaCL/build/parser.cc"
    break;

  case 25: // expr: expr "&&" expr
#line 150 "/home/tony/code/cxx/ParaCL/parser/grammar.y"
                    { yylhs.value.as < ptd::i_node* > () = drv->make_d_op<ptop::AND>(yystack_[2].value.as < ptd::i_node* > (), yystack_[0].value.as < ptd::i_node* > ()); }
#line 864 "/home/tony/code/cxx/ParaCL/build/parser.cc"
    break;

  case 26: // expr: expr "||" expr
#line 151 "/home/tony/code/cxx/ParaCL/parser/grammar.y"
                    { yylhs.value.as < ptd::i_node* > () = drv->make_d_op<ptop::OR> (yystack_[2].value.as < ptd::i_node* > (), yystack_[0].value.as < ptd::i_node* > ()); }
#line 870 "/home/tony/code/cxx/ParaCL/build/parser.cc"
    break;

  case 27: // expr: "!" expr
#line 152 "/home/tony/code/cxx/ParaCL/parser/grammar.y"
                    { yylhs.value.as < ptd::i_node* > () = drv->make_s_op<ptop::NOT>(yystack_[0].value.as < ptd::i_node* > ());     }
#line 876 "/home/tony/code/cxx/ParaCL/build/parser.cc"
    break;

  case 28: // expr: "-" expr
#line 153 "/home/tony/code/cxx/ParaCL/parser/grammar.y"
                            { yylhs.value.as < ptd::i_node* > () = drv->make_s_op<ptop::UNARY_MINUS>(yystack_[0].value.as < ptd::i_node* > ()); }
#line 882 "/home/tony/code/cxx/ParaCL/build/parser.cc"
    break;

  case 29: // expr: "+" expr
#line 154 "/home/tony/code/cxx/ParaCL/parser/grammar.y"
                            { yylhs.value.as < ptd::i_node* > () = yystack_[0].value.as < ptd::i_node* > (); }
#line 888 "/home/tony/code/cxx/ParaCL/build/parser.cc"
    break;

  case 30: // expr: ID "=" expr
#line 155 "/home/tony/code/cxx/ParaCL/parser/grammar.y"
                    {
        ptd::i_node* tmp = nullptr;
        ptd::scope* id_scope = drv->curr_scope_->is_visible(yystack_[2].value.as < std::string > ());

        if (!id_scope) {
            tmp = drv->make_identifier(yystack_[2].value.as < std::string > (), drv->curr_scope_);
            drv->curr_scope_->push_id(yystack_[2].value.as < std::string > ());
        }
        else tmp = drv->make_identifier(yystack_[2].value.as < std::string > (), id_scope);

        yylhs.value.as < ptd::i_node* > () = drv->make_d_op<ptop::ASSIG>(tmp, yystack_[0].value.as < ptd::i_node* > ());
    }
#line 905 "/home/tony/code/cxx/ParaCL/build/parser.cc"
    break;

  case 31: // primary_expr: "(" expr ")"
#line 169 "/home/tony/code/cxx/ParaCL/parser/grammar.y"
                           { yylhs.value.as < ptd::i_node* > () = yystack_[1].value.as < ptd::i_node* > (); }
#line 911 "/home/tony/code/cxx/ParaCL/build/parser.cc"
    break;

  case 32: // primary_expr: ID
#line 170 "/home/tony/code/cxx/ParaCL/parser/grammar.y"
      {
    ptd::scope* id_scope = drv->curr_scope_->is_visible(yystack_[0].value.as < std::string > ());

    if (!id_scope) {
        std::cerr << "This id is not visible in this scope: " << yystack_[0].value.as < std::string > () << " " << yystack_[0].location.begin << ":" << yystack_[0].location.end << std::endl;
        yylhs.value.as < ptd::i_node* > () = drv->make_identifier("UNDEFIND");
        drv->set_not_ok();
    }
    else yylhs.value.as < ptd::i_node* > () = drv->make_identifier(yystack_[0].value.as < std::string > (), id_scope);
 }
#line 926 "/home/tony/code/cxx/ParaCL/build/parser.cc"
    break;

  case 33: // primary_expr: NUMBER
#line 180 "/home/tony/code/cxx/ParaCL/parser/grammar.y"
            { yylhs.value.as < ptd::i_node* > () = drv->make_number(yystack_[0].value.as < int > ()); }
#line 932 "/home/tony/code/cxx/ParaCL/build/parser.cc"
    break;

  case 34: // primary_expr: "?"
#line 181 "/home/tony/code/cxx/ParaCL/parser/grammar.y"
            { yylhs.value.as < ptd::i_node* > () = drv->make_scan();     }
#line 938 "/home/tony/code/cxx/ParaCL/build/parser.cc"
    break;

  case 35: // if: if_start op
#line 184 "/home/tony/code/cxx/ParaCL/parser/grammar.y"
                           {
        yylhs.value.as < ptd::i_node* > () = drv->make_d_op<ptop::IF>(yystack_[1].value.as < ptd::i_node* > (), drv->curr_scope_);
        drv->reset_scope();
}
#line 947 "/home/tony/code/cxx/ParaCL/build/parser.cc"
    break;

  case 36: // if: if_start op else
#line 188 "/home/tony/code/cxx/ParaCL/parser/grammar.y"
                                {
        yylhs.value.as < ptd::i_node* > () = drv->make_t_op<ptop::IF_ELSE>(yystack_[2].value.as < ptd::i_node* > (), yystack_[0].value.as < std::pair<ptd::scope*, ptd::scope*> > ().first, yystack_[0].value.as < std::pair<ptd::scope*, ptd::scope*> > ().second);
        drv->reset_scope();
}
#line 956 "/home/tony/code/cxx/ParaCL/build/parser.cc"
    break;

  case 37: // else: else_start op
#line 194 "/home/tony/code/cxx/ParaCL/parser/grammar.y"
                    { yylhs.value.as < std::pair<ptd::scope*, ptd::scope*> > () = std::make_pair(yystack_[1].value.as < ptd::scope* > (), drv->curr_scope_); }
#line 962 "/home/tony/code/cxx/ParaCL/build/parser.cc"
    break;

  case 38: // if_start: "if" "(" expr ")"
#line 196 "/home/tony/code/cxx/ParaCL/parser/grammar.y"
                          { drv->new_scope(); yylhs.value.as < ptd::i_node* > () = yystack_[1].value.as < ptd::i_node* > (); }
#line 968 "/home/tony/code/cxx/ParaCL/build/parser.cc"
    break;

  case 39: // else_start: ELSE
#line 198 "/home/tony/code/cxx/ParaCL/parser/grammar.y"
                 {
    yylhs.value.as < ptd::scope* > () = drv->curr_scope_;
    drv->reset_scope(); drv->new_scope();
}
#line 977 "/home/tony/code/cxx/ParaCL/build/parser.cc"
    break;

  case 40: // while: while_start op
#line 203 "/home/tony/code/cxx/ParaCL/parser/grammar.y"
                      {
    yylhs.value.as < ptd::i_two_child* > () = drv->make_d_op<ptop::WHILE>(yystack_[1].value.as < ptd::i_node* > (), drv->curr_scope_);
    drv->reset_scope();
}
#line 986 "/home/tony/code/cxx/ParaCL/build/parser.cc"
    break;

  case 41: // while_start: "while" "(" expr ")"
#line 209 "/home/tony/code/cxx/ParaCL/parser/grammar.y"
                                { drv->new_scope(); yylhs.value.as < ptd::i_node* > () = yystack_[1].value.as < ptd::i_node* > (); }
#line 992 "/home/tony/code/cxx/ParaCL/build/parser.cc"
    break;

  case 42: // lang_func: "print" expr ";"
#line 211 "/home/tony/code/cxx/ParaCL/parser/grammar.y"
                             { yylhs.value.as < ptd::i_one_child* > () = drv->make_s_op<ptop::PRINT>(yystack_[1].value.as < ptd::i_node* > ()); }
#line 998 "/home/tony/code/cxx/ParaCL/build/parser.cc"
    break;


#line 1002 "/home/tony/code/cxx/ParaCL/build/parser.cc"

            default:
              break;
            }
        }
#if YY_EXCEPTIONS
      catch (const syntax_error& yyexc)
        {
          YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
          error (yyexc);
          YYERROR;
        }
#endif // YY_EXCEPTIONS
      YY_SYMBOL_PRINT ("-> $$ =", yylhs);
      yypop_ (yylen);
      yylen = 0;

      // Shift the result of the reduction.
      yypush_ (YY_NULLPTR, YY_MOVE (yylhs));
    }
    goto yynewstate;


  /*--------------------------------------.
  | yyerrlab -- here on detecting error.  |
  `--------------------------------------*/
  yyerrlab:
    // If not already recovering from an error, report this error.
    if (!yyerrstatus_)
      {
        ++yynerrs_;
        context yyctx (*this, yyla);
        std::string msg = yysyntax_error_ (yyctx);
        error (yyla.location, YY_MOVE (msg));
      }


    yyerror_range[1].location = yyla.location;
    if (yyerrstatus_ == 3)
      {
        /* If just tried and failed to reuse lookahead token after an
           error, discard it.  */

        // Return failure if at end of input.
        if (yyla.kind () == symbol_kind::S_YYEOF)
          YYABORT;
        else if (!yyla.empty ())
          {
            yy_destroy_ ("Error: discarding", yyla);
            yyla.clear ();
          }
      }

    // Else will try to reuse lookahead token after shifting the error token.
    goto yyerrlab1;


  /*---------------------------------------------------.
  | yyerrorlab -- error raised explicitly by YYERROR.  |
  `---------------------------------------------------*/
  yyerrorlab:
    /* Pacify compilers when the user code never invokes YYERROR and
       the label yyerrorlab therefore never appears in user code.  */
    if (false)
      YYERROR;

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYERROR.  */
    yypop_ (yylen);
    yylen = 0;
    YY_STACK_PRINT ();
    goto yyerrlab1;


  /*-------------------------------------------------------------.
  | yyerrlab1 -- common code for both syntax error and YYERROR.  |
  `-------------------------------------------------------------*/
  yyerrlab1:
    yyerrstatus_ = 3;   // Each real token shifted decrements this.
    // Pop stack until we find a state that shifts the error token.
    for (;;)
      {
        yyn = yypact_[+yystack_[0].state];
        if (!yy_pact_value_is_default_ (yyn))
          {
            yyn += symbol_kind::S_YYerror;
            if (0 <= yyn && yyn <= yylast_
                && yycheck_[yyn] == symbol_kind::S_YYerror)
              {
                yyn = yytable_[yyn];
                if (0 < yyn)
                  break;
              }
          }

        // Pop the current state because it cannot handle the error token.
        if (yystack_.size () == 1)
          YYABORT;

        yyerror_range[1].location = yystack_[0].location;
        yy_destroy_ ("Error: popping", yystack_[0]);
        yypop_ ();
        YY_STACK_PRINT ();
      }
    {
      stack_symbol_type error_token;

      yyerror_range[2].location = yyla.location;
      YYLLOC_DEFAULT (error_token.location, yyerror_range, 2);

      // Shift the error token.
      yy_lac_discard_ ("error recovery");
      error_token.state = state_type (yyn);
      yypush_ ("Shifting", YY_MOVE (error_token));
    }
    goto yynewstate;


  /*-------------------------------------.
  | yyacceptlab -- YYACCEPT comes here.  |
  `-------------------------------------*/
  yyacceptlab:
    yyresult = 0;
    goto yyreturn;


  /*-----------------------------------.
  | yyabortlab -- YYABORT comes here.  |
  `-----------------------------------*/
  yyabortlab:
    yyresult = 1;
    goto yyreturn;


  /*-----------------------------------------------------.
  | yyreturn -- parsing is finished, return the result.  |
  `-----------------------------------------------------*/
  yyreturn:
    if (!yyla.empty ())
      yy_destroy_ ("Cleanup: discarding lookahead", yyla);

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYABORT or YYACCEPT.  */
    yypop_ (yylen);
    YY_STACK_PRINT ();
    while (1 < yystack_.size ())
      {
        yy_destroy_ ("Cleanup: popping", yystack_[0]);
        yypop_ ();
      }

    return yyresult;
  }
#if YY_EXCEPTIONS
    catch (...)
      {
        YYCDEBUG << "Exception caught: cleaning lookahead and stack\n";
        // Do not try to display the values of the reclaimed symbols,
        // as their printers might throw an exception.
        if (!yyla.empty ())
          yy_destroy_ (YY_NULLPTR, yyla);

        while (1 < yystack_.size ())
          {
            yy_destroy_ (YY_NULLPTR, yystack_[0]);
            yypop_ ();
          }
        throw;
      }
#endif // YY_EXCEPTIONS
  }

  void
  parser::error (const syntax_error& yyexc)
  {
    error (yyexc.location, yyexc.what ());
  }

  const char *
  parser::symbol_name (symbol_kind_type yysymbol)
  {
    static const char *const yy_sname[] =
    {
    "end of file", "error", "invalid token", "+", "-", "*", "/", "?", "=",
  "(", ")", "{", "}", ";", ">", ">=", "<", "<=", "==", "!=", "%", "!",
  "&&", "||", "if", "while", "print", "ERR", "THEN", "ELSE", "else",
  "UPLUS", "UMINUS", "NUMBER", "ID", "$accept", "program", "scope", "op",
  "scope_br", "scope_br_start", "expr", "primary_expr", "if", "else",
  "if_start", "else_start", "while", "while_start", "lang_func", YY_NULLPTR
    };
    return yy_sname[yysymbol];
  }



  // parser::context.
  parser::context::context (const parser& yyparser, const symbol_type& yyla)
    : yyparser_ (yyparser)
    , yyla_ (yyla)
  {}

  int
  parser::context::expected_tokens (symbol_kind_type yyarg[], int yyargn) const
  {
    // Actual number of expected tokens
    int yycount = 0;

#if YYDEBUG
    // Execute LAC once. We don't care if it is successful, we
    // only do it for the sake of debugging output.
    if (!yyparser_.yy_lac_established_)
      yyparser_.yy_lac_check_ (yyla_.kind ());
#endif

    for (int yyx = 0; yyx < YYNTOKENS; ++yyx)
      {
        symbol_kind_type yysym = YY_CAST (symbol_kind_type, yyx);
        if (yysym != symbol_kind::S_YYerror
            && yysym != symbol_kind::S_YYUNDEF
            && yyparser_.yy_lac_check_ (yysym))
          {
            if (!yyarg)
              ++yycount;
            else if (yycount == yyargn)
              return 0;
            else
              yyarg[yycount++] = yysym;
          }
      }
    if (yyarg && yycount == 0 && 0 < yyargn)
      yyarg[0] = symbol_kind::S_YYEMPTY;
    return yycount;
  }




  bool
  parser::yy_lac_check_ (symbol_kind_type yytoken) const
  {
    // Logically, the yylac_stack's lifetime is confined to this function.
    // Clear it, to get rid of potential left-overs from previous call.
    yylac_stack_.clear ();
    // Reduce until we encounter a shift and thereby accept the token.
#if YYDEBUG
    YYCDEBUG << "LAC: checking lookahead " << symbol_name (yytoken) << ':';
#endif
    std::ptrdiff_t lac_top = 0;
    while (true)
      {
        state_type top_state = (yylac_stack_.empty ()
                                ? yystack_[lac_top].state
                                : yylac_stack_.back ());
        int yyrule = yypact_[+top_state];
        if (yy_pact_value_is_default_ (yyrule)
            || (yyrule += yytoken) < 0 || yylast_ < yyrule
            || yycheck_[yyrule] != yytoken)
          {
            // Use the default action.
            yyrule = yydefact_[+top_state];
            if (yyrule == 0)
              {
                YYCDEBUG << " Err\n";
                return false;
              }
          }
        else
          {
            // Use the action from yytable.
            yyrule = yytable_[yyrule];
            if (yy_table_value_is_error_ (yyrule))
              {
                YYCDEBUG << " Err\n";
                return false;
              }
            if (0 < yyrule)
              {
                YYCDEBUG << " S" << yyrule << '\n';
                return true;
              }
            yyrule = -yyrule;
          }
        // By now we know we have to simulate a reduce.
        YYCDEBUG << " R" << yyrule - 1;
        // Pop the corresponding number of values from the stack.
        {
          std::ptrdiff_t yylen = yyr2_[yyrule];
          // First pop from the LAC stack as many tokens as possible.
          std::ptrdiff_t lac_size = std::ptrdiff_t (yylac_stack_.size ());
          if (yylen < lac_size)
            {
              yylac_stack_.resize (std::size_t (lac_size - yylen));
              yylen = 0;
            }
          else if (lac_size)
            {
              yylac_stack_.clear ();
              yylen -= lac_size;
            }
          // Only afterwards look at the main stack.
          // We simulate popping elements by incrementing lac_top.
          lac_top += yylen;
        }
        // Keep top_state in sync with the updated stack.
        top_state = (yylac_stack_.empty ()
                     ? yystack_[lac_top].state
                     : yylac_stack_.back ());
        // Push the resulting state of the reduction.
        state_type state = yy_lr_goto_state_ (top_state, yyr1_[yyrule]);
        YYCDEBUG << " G" << int (state);
        yylac_stack_.push_back (state);
      }
  }

  // Establish the initial context if no initial context currently exists.
  bool
  parser::yy_lac_establish_ (symbol_kind_type yytoken)
  {
    /* Establish the initial context for the current lookahead if no initial
       context is currently established.

       We define a context as a snapshot of the parser stacks.  We define
       the initial context for a lookahead as the context in which the
       parser initially examines that lookahead in order to select a
       syntactic action.  Thus, if the lookahead eventually proves
       syntactically unacceptable (possibly in a later context reached via a
       series of reductions), the initial context can be used to determine
       the exact set of tokens that would be syntactically acceptable in the
       lookahead's place.  Moreover, it is the context after which any
       further semantic actions would be erroneous because they would be
       determined by a syntactically unacceptable token.

       yy_lac_establish_ should be invoked when a reduction is about to be
       performed in an inconsistent state (which, for the purposes of LAC,
       includes consistent states that don't know they're consistent because
       their default reductions have been disabled).

       For parse.lac=full, the implementation of yy_lac_establish_ is as
       follows.  If no initial context is currently established for the
       current lookahead, then check if that lookahead can eventually be
       shifted if syntactic actions continue from the current context.  */
    if (yy_lac_established_)
      return true;
    else
      {
#if YYDEBUG
        YYCDEBUG << "LAC: initial context established for "
                 << symbol_name (yytoken) << '\n';
#endif
        yy_lac_established_ = true;
        return yy_lac_check_ (yytoken);
      }
  }

  // Discard any previous initial lookahead context.
  void
  parser::yy_lac_discard_ (const char* event)
  {
   /* Discard any previous initial lookahead context because of Event,
      which may be a lookahead change or an invalidation of the currently
      established initial context for the current lookahead.

      The most common example of a lookahead change is a shift.  An example
      of both cases is syntax error recovery.  That is, a syntax error
      occurs when the lookahead is syntactically erroneous for the
      currently established initial context, so error recovery manipulates
      the parser stacks to try to find a new initial context in which the
      current lookahead is syntactically acceptable.  If it fails to find
      such a context, it discards the lookahead.  */
    if (yy_lac_established_)
      {
        YYCDEBUG << "LAC: initial context discarded due to "
                 << event << '\n';
        yy_lac_established_ = false;
      }
  }


  int
  parser::yy_syntax_error_arguments_ (const context& yyctx,
                                                 symbol_kind_type yyarg[], int yyargn) const
  {
    /* There are many possibilities here to consider:
       - If this state is a consistent state with a default action, then
         the only way this function was invoked is if the default action
         is an error action.  In that case, don't check for expected
         tokens because there are none.
       - The only way there can be no lookahead present (in yyla) is
         if this state is a consistent state with a default action.
         Thus, detecting the absence of a lookahead is sufficient to
         determine that there is no unexpected or expected token to
         report.  In that case, just report a simple "syntax error".
       - Don't assume there isn't a lookahead just because this state is
         a consistent state with a default action.  There might have
         been a previous inconsistent state, consistent state with a
         non-default action, or user semantic action that manipulated
         yyla.  (However, yyla is currently not documented for users.)
         In the first two cases, it might appear that the current syntax
         error should have been detected in the previous state when
         yy_lac_check was invoked.  However, at that time, there might
         have been a different syntax error that discarded a different
         initial context during error recovery, leaving behind the
         current lookahead.
    */

    if (!yyctx.lookahead ().empty ())
      {
        if (yyarg)
          yyarg[0] = yyctx.token ();
        int yyn = yyctx.expected_tokens (yyarg ? yyarg + 1 : yyarg, yyargn - 1);
        return yyn + 1;
      }
    return 0;
  }

  // Generate an error message.
  std::string
  parser::yysyntax_error_ (const context& yyctx) const
  {
    // Its maximum.
    enum { YYARGS_MAX = 5 };
    // Arguments of yyformat.
    symbol_kind_type yyarg[YYARGS_MAX];
    int yycount = yy_syntax_error_arguments_ (yyctx, yyarg, YYARGS_MAX);

    char const* yyformat = YY_NULLPTR;
    switch (yycount)
      {
#define YYCASE_(N, S)                         \
        case N:                               \
          yyformat = S;                       \
        break
      default: // Avoid compiler warnings.
        YYCASE_ (0, YY_("syntax error"));
        YYCASE_ (1, YY_("syntax error, unexpected %s"));
        YYCASE_ (2, YY_("syntax error, unexpected %s, expecting %s"));
        YYCASE_ (3, YY_("syntax error, unexpected %s, expecting %s or %s"));
        YYCASE_ (4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
        YYCASE_ (5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
      }

    std::string yyres;
    // Argument number.
    std::ptrdiff_t yyi = 0;
    for (char const* yyp = yyformat; *yyp; ++yyp)
      if (yyp[0] == '%' && yyp[1] == 's' && yyi < yycount)
        {
          yyres += symbol_name (yyarg[yyi++]);
          ++yyp;
        }
      else
        yyres += *yyp;
    return yyres;
  }


  const signed char parser::yypact_ninf_ = -22;

  const signed char parser::yytable_ninf_ = -1;

  const short
  parser::yypact_[] =
  {
      50,    61,    61,   -22,    61,   -22,   -22,    61,    -8,    -1,
      61,   -22,     3,    17,   -22,    50,   -22,    50,    83,   -22,
     -22,    50,   -22,    50,   -22,   -22,   -22,   104,   -22,    61,
      61,   125,    61,   -22,   -22,    -2,    61,    61,    61,    61,
     -22,    61,    61,    61,    61,    61,    61,    61,    61,    61,
      -9,   -22,   -22,   146,   167,   -22,   188,   -22,    13,    13,
     -22,   -22,   236,   236,   236,   236,    10,    10,   -22,   229,
     209,   -22,   -22,    50,   -22,   -22,   -22
  };

  const signed char
  parser::yydefact_[] =
  {
       4,     0,     0,    34,     0,    12,    10,     0,     0,     0,
       0,    33,    32,     0,     2,     4,     9,     4,     0,    13,
       7,     0,     6,     0,     8,    29,    28,     0,    27,     0,
       0,     0,     0,     1,     3,     0,     0,     0,     0,     0,
       5,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      35,    40,    31,     0,     0,    42,    30,    11,    14,    15,
      16,    17,    19,    20,    21,    22,    23,    24,    18,    25,
      26,    39,    36,     0,    38,    41,    37
  };

  const signed char
  parser::yypgoto_[] =
  {
     -22,   -22,   -10,   -21,   -22,   -22,     2,   -22,   -22,   -22,
     -22,   -22,   -22,   -22,   -22
  };

  const signed char
  parser::yydefgoto_[] =
  {
       0,    13,    14,    15,    16,    17,    18,    19,    20,    72,
      21,    73,    22,    23,    24
  };

  const signed char
  parser::yytable_[] =
  {
      50,    29,    51,    25,    26,    34,    27,    35,    30,    28,
      57,    32,    31,    36,    37,    38,    39,    33,    38,    39,
      71,     0,     0,     0,    41,    42,    43,    44,    -1,    -1,
      47,    53,    54,    47,    56,     0,     0,     0,    58,    59,
      60,    61,     0,    62,    63,    64,    65,    66,    67,    68,
      69,    70,    76,     1,     2,     0,     0,     3,     0,     4,
       0,     5,     0,     6,     1,     2,     0,     0,     3,     0,
       4,     7,     0,     0,     8,     9,    10,     0,     0,     0,
       0,     0,     7,    11,    12,     0,    36,    37,    38,    39,
       0,     0,     0,     0,    11,    12,    40,    41,    42,    43,
      44,    45,    46,    47,     0,    48,    49,    36,    37,    38,
      39,     0,     0,     0,    52,     0,     0,     0,    41,    42,
      43,    44,    45,    46,    47,     0,    48,    49,    36,    37,
      38,    39,     0,     0,     0,     0,     0,     0,    55,    41,
      42,    43,    44,    45,    46,    47,     0,    48,    49,    36,
      37,    38,    39,     0,     0,     0,    74,     0,     0,     0,
      41,    42,    43,    44,    45,    46,    47,     0,    48,    49,
      36,    37,    38,    39,     0,     0,     0,    75,     0,     0,
       0,    41,    42,    43,    44,    45,    46,    47,     0,    48,
      49,    36,    37,    38,    39,     0,     0,     0,     0,     0,
       0,     0,    41,    42,    43,    44,    45,    46,    47,     0,
      48,    49,    36,    37,    38,    39,     0,     0,     0,     0,
       0,     0,     0,    41,    42,    43,    44,    45,    46,    47,
       0,    48,    36,    37,    38,    39,     0,     0,     0,    36,
      37,    38,    39,    41,    42,    43,    44,    45,    46,    47,
      -1,    -1,    -1,    -1,     0,     0,    47
  };

  const signed char
  parser::yycheck_[] =
  {
      21,     9,    23,     1,     2,    15,     4,    17,     9,     7,
      12,     8,    10,     3,     4,     5,     6,     0,     5,     6,
      29,    -1,    -1,    -1,    14,    15,    16,    17,    18,    19,
      20,    29,    30,    20,    32,    -1,    -1,    -1,    36,    37,
      38,    39,    -1,    41,    42,    43,    44,    45,    46,    47,
      48,    49,    73,     3,     4,    -1,    -1,     7,    -1,     9,
      -1,    11,    -1,    13,     3,     4,    -1,    -1,     7,    -1,
       9,    21,    -1,    -1,    24,    25,    26,    -1,    -1,    -1,
      -1,    -1,    21,    33,    34,    -1,     3,     4,     5,     6,
      -1,    -1,    -1,    -1,    33,    34,    13,    14,    15,    16,
      17,    18,    19,    20,    -1,    22,    23,     3,     4,     5,
       6,    -1,    -1,    -1,    10,    -1,    -1,    -1,    14,    15,
      16,    17,    18,    19,    20,    -1,    22,    23,     3,     4,
       5,     6,    -1,    -1,    -1,    -1,    -1,    -1,    13,    14,
      15,    16,    17,    18,    19,    20,    -1,    22,    23,     3,
       4,     5,     6,    -1,    -1,    -1,    10,    -1,    -1,    -1,
      14,    15,    16,    17,    18,    19,    20,    -1,    22,    23,
       3,     4,     5,     6,    -1,    -1,    -1,    10,    -1,    -1,
      -1,    14,    15,    16,    17,    18,    19,    20,    -1,    22,
      23,     3,     4,     5,     6,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    14,    15,    16,    17,    18,    19,    20,    -1,
      22,    23,     3,     4,     5,     6,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    14,    15,    16,    17,    18,    19,    20,
      -1,    22,     3,     4,     5,     6,    -1,    -1,    -1,     3,
       4,     5,     6,    14,    15,    16,    17,    18,    19,    20,
      14,    15,    16,    17,    -1,    -1,    20
  };

  const signed char
  parser::yystos_[] =
  {
       0,     3,     4,     7,     9,    11,    13,    21,    24,    25,
      26,    33,    34,    36,    37,    38,    39,    40,    41,    42,
      43,    45,    47,    48,    49,    41,    41,    41,    41,     9,
       9,    41,     8,     0,    37,    37,     3,     4,     5,     6,
      13,    14,    15,    16,    17,    18,    19,    20,    22,    23,
      38,    38,    10,    41,    41,    13,    41,    12,    41,    41,
      41,    41,    41,    41,    41,    41,    41,    41,    41,    41,
      41,    29,    44,    46,    10,    10,    38
  };

  const signed char
  parser::yyr1_[] =
  {
       0,    35,    36,    37,    37,    38,    38,    38,    38,    38,
      38,    39,    40,    41,    41,    41,    41,    41,    41,    41,
      41,    41,    41,    41,    41,    41,    41,    41,    41,    41,
      41,    42,    42,    42,    42,    43,    43,    44,    45,    46,
      47,    48,    49
  };

  const signed char
  parser::yyr2_[] =
  {
       0,     2,     1,     2,     0,     2,     1,     1,     1,     1,
       1,     3,     1,     1,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     2,     2,     2,
       3,     3,     1,     1,     1,     2,     3,     2,     4,     1,
       2,     4,     3
  };




#if YYDEBUG
  const unsigned char
  parser::yyrline_[] =
  {
       0,   114,   114,   122,   123,   126,   127,   128,   129,   130,
     131,   134,   136,   138,   139,   140,   141,   142,   143,   144,
     145,   146,   147,   148,   149,   150,   151,   152,   153,   154,
     155,   169,   170,   180,   181,   184,   188,   194,   196,   198,
     203,   209,   211
  };

  void
  parser::yy_stack_print_ () const
  {
    *yycdebug_ << "Stack now";
    for (stack_type::const_iterator
           i = yystack_.begin (),
           i_end = yystack_.end ();
         i != i_end; ++i)
      *yycdebug_ << ' ' << int (i->state);
    *yycdebug_ << '\n';
  }

  void
  parser::yy_reduce_print_ (int yyrule) const
  {
    int yylno = yyrline_[yyrule];
    int yynrhs = yyr2_[yyrule];
    // Print the symbols being reduced, and their result.
    *yycdebug_ << "Reducing stack by rule " << yyrule - 1
               << " (line " << yylno << "):\n";
    // The symbols being reduced.
    for (int yyi = 0; yyi < yynrhs; yyi++)
      YY_SYMBOL_PRINT ("   $" << yyi + 1 << " =",
                       yystack_[(yynrhs) - (yyi + 1)]);
  }
#endif // YYDEBUG


} // yy
#line 1642 "/home/tony/code/cxx/ParaCL/build/parser.cc"

#line 213 "/home/tony/code/cxx/ParaCL/parser/grammar.y"


namespace yy {
    void parser::error(const location_type& lcn, const std::string& msg) {
        std::cerr << lcn << ": " << msg << '\n';
    }
}
