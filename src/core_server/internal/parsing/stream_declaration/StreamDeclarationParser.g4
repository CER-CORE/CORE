parser grammar StreamDeclarationParser;

options {
  tokenVocab = StreamDeclarationLexer;
}

parse
 : (core_stmt | error )* EOF
 ;

error
 : UNEXPECTED_CHAR
   {
     throw new RuntimeException("UNEXPECTED_CHAR=" + $UNEXPECTED_CHAR.text);
   }
 ;

core_stmt
 : core_query
 | core_declaration
 ;

core_declaration
 : event_declaration
 | stream_declaration
 ;

event_declaration
 : K_DECLARE K_EVENT event_name '(' attribute_dec_list ')'
 ;

attribute_dec_list
 :
 | attribute_declaration ( ',' attribute_declaration )*
 ;

attribute_declaration
 : attribute_name datatype
 ;

datatype
 : 'int'
 | 'string'
 | 'double'
 | 'long'
 | 'boolean'
 | IDENTIFIER
 ;

stream_declaration
 : K_DECLARE K_STREAM stream_name '(' event_list? ')'
 ;

event_list
 : event_name ( ',' event_name )*
 ;

core_query
 : K_SELECT selection_strategy? result_values
   ( K_FROM stream_name ( ',' stream_name )* )?
   K_WHERE core_pattern
   ( K_PARTITION K_BY partition_list )?
   ( K_WITHIN time_window )?
   ( K_CONSUME K_BY consumption_policy )?
 ;

selection_strategy
 : K_ALL                        # ss_all
 | K_ANY                        # ss_any
 | K_LAST                       # ss_last
 | K_MAX                        # ss_max
 | K_NEXT                       # ss_next
 | K_STRICT                     # ss_strict
 ;

result_values
 : STAR
 | s_event_name ( ',' s_event_name )*
 ;


core_pattern
 : '(' core_pattern ')'                                 # par_core_pattern
 | s_event_name                                         # event_core_pattern
 | core_pattern K_AS event_name                         # assign_core_pattern
 | core_pattern '+'                                     # kleene_core_pattern
 | core_pattern ( K_OR | SEMICOLON ) core_pattern       # binary_core_pattern
 | core_pattern K_FILTER filter                         # filter_core_pattern
 ;

partition_list
 : '[' attribute_list ']' (',' '[' attribute_list ']')?
 ;

attribute_list
 :  attribute_name ( ',' attribute_name )*
 ;

consumption_policy
 : K_ANY                                                # cp_any
 | K_PARTITION                                          # cp_partition
 | K_NONE                                               # cp_none
 ;

filter
 : '(' filter ')'                                       # par_filter
 | event_name '[' bool_expr ']'                         # event_filter
 | filter K_AND filter                                  # and_filter
 | filter K_OR filter                                   # or_filter
 ;

bool_expr
 : '(' bool_expr ')'                                           # par_bool_expr
 | K_NOT bool_expr                                             # not_expr
 | math_expr ( LE | LEQ | GE | GEQ ) math_expr                 # inequality_expr
 | math_expr ( EQ | NEQ ) math_expr                            # equality_math_expr
 | bool_expr K_AND bool_expr                                   # and_expr
 | bool_expr K_OR bool_expr                                    # or_expr
 | attribute_name K_LIKE REGEXP                                # regex_expr
 | attribute_name ( K_IN | K_NOT K_IN ) value_seq              # containment_expr
 | string_literal ( EQ | NEQ ) string_literal_or_regexp        # equality_string_expr
 ;

string_literal
 : string
 | attribute_name
 ;

string_literal_or_regexp
 : string
 | attribute_name
 | REGEXP
 ;

math_expr
 : '(' math_expr ')'                                        # par_math_expr
 | number                                                   # number_math_expr
 | attribute_name                                           # attribute_math_expr
 | ( PLUS | MINUS ) math_expr                               # unary_math_expr
 | math_expr ( STAR | SLASH | PERCENT ) math_expr           # mul_math_expr
 | math_expr ( PLUS | MINUS ) math_expr                     # sum_math_expr
 ;

value_seq
 : '{' number_seq '}'
 | '{' string_seq '}'
 ;

number_seq
 : number (',' number)*            # number_list
 | number '..' number              # number_range
 | number '..'                     # number_range_lower
 | '..' number                     # number_range_upper
 ;

string_seq
 : string (',' string)*
 ;

time_window
 : event_span
 | time_span
 | custom_span
 ;

event_span
 : integer K_EVENTS
 ;

time_span
 : hour_span? minute_span? second_span?
 ;

hour_span
 : integer K_HOURS
 ;

minute_span
 : integer K_MINUTES
 ;

second_span
 : integer K_SECONDS
 ;

custom_span
 : integer '[' any_name ']'
 ;

named_event
 : s_event_name ( K_AS event_name )?
 ;

s_event_name
 : ( stream_name '>' ) ? event_name
 ;

event_name
 : any_name
 ;

stream_name
 : any_name
 ;

attribute_name
 : any_name
 ;

integer
 : INTEGER_LITERAL
 ;

number
 : FLOAT_LITERAL
 | INTEGER_LITERAL
 ;

string
 : STRING_LITERAL
 ;

any_name
 : IDENTIFIER
 ;

keyword
 : K_ALL
 | K_AND
 | K_ANY
 | K_AS
 | K_BY
 | K_CONSUME
 | K_DECLARE
 | K_DISTINCT
 | K_EVENT
 | K_EVENTS
 | K_FILTER
 | K_FROM
 | K_HOURS
 | K_IN
 | K_LAST
 | K_LIKE
 | K_MAX
 | K_MINUTES
 | K_NEXT
 | K_NONE
 | K_NOT
 | K_OR
 | K_PARTITION
 | K_SECONDS
 | K_SELECT
 | K_STREAM
 | K_STRICT
 | K_UNLESS
 | K_WHERE
 | K_WITHIN
 ;
