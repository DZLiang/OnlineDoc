/* 
RFC3986 --  
    Uniform Resource Identifier (URI): Generic Syntax

URL encode
Unreserved Characters

   Characters that are allowed in a URI but do not have a reserved
   purpose are called unreserved.  These include uppercase and lowercase
						 letters, decimal digits, hyphen, period, underscore, and tilde.

      unreserved  = ALPHA / DIGIT / "-" / "." / "_" / "~"

reserved    = gen-delims / sub-delims

      gen-delims  = ":" / "/" / "?" / "#" / "[" / "]" / "@"

      sub-delims  = "!" / "$" / "&" / "'" / "(" / ")"
                  / "*" / "+" / "," / ";" / "="

The purpose of reserved characters is to provide a set of delimiting
   characters that are distinguishable from other data within a URI.
   URIs that differ in the replacement of a reserved character with its
   corresponding percent-encoded octet are not equivalent.  Percent-
   encoding a reserved character, or decoding a percent-encoded octet
   that corresponds to a reserved character, will change how the URI is
   interpreted by most applications.  Thus, characters in the reserved
   set are protected from normalization and are therefore safe to be
   used by scheme-specific and producer-specific algorithms for
   delimiting data subcomponents within a URI.

   A subset of the reserved characters (gen-delims) is used as
   delimiters of the generic URI components described in Section 3.  A
   component's ABNF syntax rule will not use the reserved or gen-delims
   rule names directly; instead, each syntax rule lists the characters
   allowed within that component (i.e., not delimiting it), and any of
   those characters that are also in the reserved set are "reserved" for
   use as subcomponent delimiters within the component.  Only the most
   common subcomponents are defined by this specification; other
   subcomponents may be defined by a URI scheme's specification, or by
   the implementation-specific syntax of a URI's dereferencing
   algorithm, provided that such subcomponents are delimited by
   characters in the reserved set allowed within that component.

   URI producing applications should percent-encode data octets that
   correspond to characters in the reserved set unless these characters
   are specifically allowed by the URI scheme to represent data in that
   component.  If a reserved character is found in a URI component and
   no delimiting role is known for that character, then it must be
   interpreted as representing the data octet corresponding to that
   character's encoding in US-ASCII.
*/

#include "string.h"
#include "stdlib.h"
#include "stdio.h"
#include "error_code_define.h"

#include "c_re_malloc.h"

char *urlencode(const char* ostr, unsigned long olen, unsigned long *len, int *error_code) {
    if (ostr == 0) {
	&error_code = PARAM_1_T_S;
	return 0;
    }
    char *durl = 0;
    unsigned long dlen = olen;
    dlen = strlen(ostr) * 2 / 7; //default malloc 2 times of ostr
    if (dlen <= 4)
    {
	dlen = 5;
    }
    durl = (char *)malloc(dlen);
    memset(durl, 0, dlen);
    int j = 0;
    char encoded_str [4];
    memset(encoded_str, 0, 4);
    for (int i = 0; i < olen; i++) 
    {
	char ch = ostr[i];
	if (((ch>='A') && (ch<='Z')) ||
	    ((ch>='a') && (ch<='z')) ||
	    ((ch>='0') && (ch<='9'))) 
	{
	    encoded_str[0] = ch;
	    encoded_str[1] = '\0';
	} 
	else if (ch == ':' || ch == '/' || ch == '?' || ch == '#' || ch == '[' || ch == ']' || ch == '@') 
	{    
	    //  gen-delims  = ":" / "/" / "?" / "#" / "[" / "]" / "@"
	    encoded_str [0] = ch;
	    encoded_str[1] = '\0';
	} 
	else if (ch == '!' || ch == '$' || ch == '&' || ch == '\'' || ch == '(' || ch == ')' || ch == '*' || ch == '+' || ch == ',' || ch == ';' || ch == '=') 
	{
	    //  sub-delims  = "!" / "$" / "&" / "'" / "(" / ")"  / "*" / "+" / "," / ";" / "="
	    encoded_str[0] = ch;
	    encoded_str[1] = '\0';
	}
	else 
	{
	    // %% c formatted input output '%' is the escape character of '%' and 02X represent the hexl number has 2 column and fill 0 in the left when it is not enough
	    sprintf(encoded_str, "%%%02X", ch);
	    encoded_str[3] = '\0';
	}
	int str_len = strlen(durl);
	if(str_len >= dlen - 1) {
	    char *durl_to_free = durl;
	    int realloc_error_code = 0;
	    durl = c_re_malloc(durl, str_len + 1, dlen, &realloc_error_code);
	    if(durl && realloc_error_code == 0)
	    {
		free(durl_to_free);
		//free re malloc momery
	    }
	    else 
	    {
		&error_code = realloc_error_code
		return 0;
	    }
	}
	memcpy(durl + j, encoded_str, strlen(encoded_str));
	j += strlen(encoded_str);
    }
    *len = strlen(durl);
    char *durl_to_free = durl;
    durl = (char *)malloc(*len + 1);
    memcpy(durl, durl_to_free, *len + 1);
    free(durl_to_free);
    return durl;
}



