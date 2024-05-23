/*
 * err.h
 *
 * Standard error handling mechanism
 *
 * SOFTWARE RIGHTS
 *
 * We reserve no LEGAL rights to the Purdue Compiler Construction Tool
 * Set (PCCTS) -- PCCTS is in the public domain.  An individual or
 * company may do whatever they wish with source code distributed with
 * PCCTS or the code generated by PCCTS, including the incorporation of
 * PCCTS, or its output, into commerical software.
 *
 * We encourage users to develop software with PCCTS.  However, we do ask
 * that credit is given to us for developing PCCTS.  By "credit",
 * we mean that if you incorporate our source code into one of your
 * programs (commercial product, research project, or otherwise) that you
 * acknowledge this fact somewhere in the documentation, research report,
 * etc...  If you like PCCTS and have developed a nice tool with the
 * output, please mention that you developed it using PCCTS.  In
 * addition, we ask that this header remain intact in our source code.
 * As long as these guidelines are kept, we expect to continue enhancing
 * this system and expect to make other tools available as they are
 * completed.
 *
 * Has grown to hold all kinds of stuff (err.h is increasingly misnamed)
 *
 * ANTLR 1.33
 * Terence Parr
 * Parr Research Corporation
 * with Purdue University and AHPCRC, University of Minnesota
 * 1989-2000
 */

#ifndef ERR_H
#define ERR_H

#include "pcctscfg.h"
#include <stdlib.h>
#include <assert.h>

/*									      */
/*  7-Apr-97  133MR1							      */
/*		Proper choice of STDC and cplusplus pre-processor symbols (?) */
/*									      */
#include "pccts_string.h"

#ifdef PCCTS_USE_STDARG
#include "pccts_stdarg.h"
#else
#include <varargs.h>
#endif

#ifdef DUM
/* Define usable bits per unsigned int word (used for set stuff) */
#ifdef PC
#define BSETWORDSIZE 16
#define BSETLOGWORDSIZE	4
#else
#define	BSETWORDSIZE 32
#define BSETLOGWORDSIZE 5
#endif
#endif

#define	BSETWORDSIZE 8
#define BSETLOGWORDSIZE 3		/* SetWordType is 8bits */

#define	BSETMODWORD(x) ((x) & (BSETWORDSIZE-1))		/* x % BSETWORDSIZE */
#define	BSETDIVWORD(x) ((x) >> BSETLOGWORDSIZE)		/* x / BSETWORDSIZE */

/* This is not put into the global pccts_parser structure because it is
 * hidden and does not need to be saved during a "save state" operation
 */
/* maximum of 32 bits/unsigned int and must be 8 bits/byte */
static SetWordType bitmask[] = {
	0x00000001, 0x00000002, 0x00000004, 0x00000008,
	0x00000010, 0x00000020, 0x00000040, 0x00000080
};

#ifdef zzTRACE_RULES
int  zzTraceOptionValueDefault=1;
int  zzTraceOptionValue=1;
int  zzTraceGuessOptionValue=1;
char *zzTraceCurrentRuleName=NULL;
int  zzTraceDepth=0;
#endif

int  zzGuessSeq=0;          /* MR10 */
int  zzSyntaxErrCount=0;    /* MR11 */
int  zzLexErrCount=0;       /* MR11 */

void
#ifdef __USE_PROTOS
zzresynch(SetWordType *wd,SetWordType mask)
#else
zzresynch(wd,mask)
SetWordType *wd, mask;
#endif
{
	static int consumed = 1;

	/* if you enter here without having consumed a token from last resynch
	 * force a token consumption.
	 */
	if ( !consumed ) {zzCONSUME; consumed=1; return;}   /* MR10 */

	/* if current token is in resynch set, we've got what we wanted */
	if ( wd[LA(1)]&mask || LA(1) == zzEOF_TOKEN ) {consumed=0; return;}
	
	/* scan until we find something in the resynch set */
	while ( !(wd[LA(1)]&mask) && LA(1) != zzEOF_TOKEN ) {zzCONSUME;}
	consumed=1;
}

/*                                                                          */
/*  7-Apr-97 133MR1 for C++ and MR7 for C                                   */
/*   	     Change suggested by Eli Sternheim (eli@interhdl.com)           */
/*                                                                          */

void
#ifdef __USE_PROTOS
zzconsumeUntil(SetWordType *st)
#else
zzconsumeUntil(st)
SetWordType *st;
#endif
{
    int     tmp;                                                     /* MR7 */
	while ( !zzset_el( (tmp=LA(1)), st) && tmp!=1 /* Eof */) {       /* MR7 */
                                                      zzCONSUME; }   /* MR7 */
}

/*                                                                          */
/*  7-Apr-97 133MR1 for C++ and MR7 for C                                   */
/*   	     Change suggested by Eli Sternheim (eli@interhdl.com)           */
/*                                                                          */

void
#ifdef __USE_PROTOS
zzconsumeUntilToken(int t)
#else
zzconsumeUntilToken(t)
int t;
#endif
{
    int     tmp;                                                     /* MR7 */
	while ( (tmp=LA(1)) !=t && tmp!=1 /* Eof */) { zzCONSUME; }      /* MR7 */
}

/* input looks like:
 *		zzFAIL(k, e1, e2, ...,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText)
 * where the zzMiss stuff is set here to the token that did not match
 * (and which set wasn't it a member of).
 */

#ifdef PCCTS_USE_STDARG
void zzFAIL(int k, ...)
#else
void zzFAIL(va_alist)
va_dcl
#endif
{
#ifdef LL_K
	static char text[LL_K*ZZLEXBUFSIZE+1];
	SetWordType *f[LL_K];
#else
	static char text[ZZLEXBUFSIZE+1];
	SetWordType *f[1];
#endif
	SetWordType **miss_set;
	char **miss_text;
	int *bad_tok;
	char **bad_text;
	int *err_k;
	int i;
	va_list ap;
#ifndef PCCTS_USE_STDARG			/* MR20 */
	int k;
#endif
#ifdef PCCTS_USE_STDARG         /* MR20 */
	va_start(ap, k);
#else
	va_start(ap);
	k = va_arg(ap, int);	/* how many lookahead sets? */
#endif
    assert(k <= sizeof(f)/sizeof(f[0]));    /* MR20 G. Hobbelt */
	text[0] = '\0';
	for (i=1; i<=k; i++)	/* collect all lookahead sets */
	{
		f[i-1] = va_arg(ap, SetWordType *);
	}
	for (i=1; i<=k; i++)	/* look for offending token */
	{
		if ( i>1 ) strcat(text, " ");
		strcat(text, LATEXT(i));
		if ( !zzset_el((unsigned)LA(i), f[i-1]) ) break;
	}
	miss_set = va_arg(ap, SetWordType **);
	miss_text = va_arg(ap, char **);
	bad_tok = va_arg(ap, int *);
	bad_text = va_arg(ap, char **);
	err_k = va_arg(ap, int *);
	if ( i>k )
	{
		/* bad; lookahead is permutation that cannot be matched,
		 * but, the ith token of lookahead is valid at the ith position
		 * (The old LL sub 1 (k) versus LL(k) parsing technique)
		 */
		*miss_set = NULL;
		*miss_text = zzlextext;
		*bad_tok = LA(1);
		*bad_text = LATEXT(1);
		*err_k = k;
		return;
	}
/*	fprintf(stderr, "%s not in %dth set\n", zztokens[LA(i)], i);*/
	*miss_set = f[i-1];
	*miss_text = text;
	*bad_tok = LA(i);
	*bad_text = LATEXT(i);
	if ( i==1 ) *err_k = 1;
	else *err_k = k;
}

#ifdef __USE_PROTOS
void zzTraceGuessDone(zzantlr_state *state)
#else
void zzTraceGuessDone(state)
  zzantlr_state     *state;
#endif
{
#ifdef zzTRACE_RULES
#ifdef ZZCAN_GUESS

  int   doIt=0;

  if (zzTraceCurrentRuleName == NULL) return;

  if (zzTraceOptionValue <= 0) {
    doIt=0;
  } else if (zzTraceGuessOptionValue <= 0) {
    doIt=0;
  } else {
    doIt=1;
  };

  if (doIt) {
    fprintf(stderr,"guess done - returning to rule %s {\"%s\"} at depth %d",
        state->traceCurrentRuleName,
        LATEXT(1),
        state->traceDepth);
    if (state->guessing != 0) {
      fprintf(stderr," (guess mode continues - an enclosing guess is still active)");
    } else {
      fprintf(stderr," (guess mode ends)");
    };
    fprintf(stderr,"\n");
  };
#endif
#endif
}

void
#ifdef __USE_PROTOS
zzsave_antlr_state(zzantlr_state *buf)
#else
zzsave_antlr_state(buf)
zzantlr_state *buf;
#endif
{
#ifdef LL_K
	int     i;
#endif

#ifdef ZZCAN_GUESS
	buf->guess_start = zzguess_start;
	buf->guessing = zzguessing;
#endif
	buf->asp = zzasp;
#ifdef GENAST
	buf->ast_sp = zzast_sp;
#endif
#ifdef ZZINF_LOOK
	buf->inf_labase = zzinf_labase;
	buf->inf_last = zzinf_last;

/* MR6 	Gunnar Rxnning (gunnar@candleweb.no)                                */
/* MR6	  Additional state needs to be saved/restored                       */

  	buf->inf_tokens = zzinf_tokens;                                  /* MR6 */
	buf->inf_text = zzinf_text;                                      /* MR6 */
	buf->inf_text_buffer = zzinf_text_buffer;                        /* MR6 */
	buf->inf_line = zzinf_line;			                             /* MR6 */

#endif
#ifdef DEMAND_LOOK
	buf->dirty = zzdirty;
#endif
#ifdef LL_K
	for (i=0; i<LL_K; i++) buf->tokenLA[i] = zztokenLA[i];
	for (i=0; i<LL_K; i++) strcpy(buf->textLA[i], zztextLA[i]);
	buf->lap = zzlap;
	buf->labase = zzlabase;
#else
	buf->token = zztoken;
	strcpy(buf->text, zzlextext);
#endif
#ifdef zzTRACE_RULES

    /* MR10 */

    buf->traceOptionValue=zzTraceOptionValue;
    buf->traceGuessOptionValue=zzTraceGuessOptionValue;
    buf->traceCurrentRuleName=zzTraceCurrentRuleName;
    buf->traceDepth=zzTraceDepth;
#endif
}

void
#ifdef __USE_PROTOS
zzrestore_antlr_state(zzantlr_state *buf)
#else
zzrestore_antlr_state(buf)
zzantlr_state *buf;
#endif
{

#ifdef zzTRACE_RULES
    int     prevTraceOptionValue;
#endif

#ifdef LL_K
	int     i;
#endif

#ifdef ZZCAN_GUESS
	zzguess_start = buf->guess_start;
	zzguessing = buf->guessing;
#endif
	zzasp = buf->asp;
#ifdef GENAST
	zzast_sp = buf->ast_sp;
#endif
#ifdef ZZINF_LOOK
	zzinf_labase = buf->inf_labase;
	zzinf_last = buf->inf_last;

/* MR6 	Gunnar Rxnning (gunnar@candleweb.no)                                */
/* MR6	  Additional state needs to be saved/restored                       */

	zzinf_tokens = buf->inf_tokens;                                  /* MR6 */
	zzinf_text = buf->inf_text;                                      /* MR6 */
	zzinf_text_buffer = buf->inf_text_buffer;                        /* MR6 */
	zzinf_line = buf->inf_line;			                             /* MR6 */
#endif
#ifdef DEMAND_LOOK
	zzdirty = buf->dirty;
#endif
#ifdef LL_K
	for (i=0; i<LL_K; i++) zztokenLA[i] = buf->tokenLA[i];
	for (i=0; i<LL_K; i++) strcpy(zztextLA[i], buf->textLA[i]);
	zzlap = buf->lap;
	zzlabase = buf->labase;
#else
	zztoken = buf->token;
	strcpy(zzlextext, buf->text);
#endif
#ifdef zzTRACE_RULES

    prevTraceOptionValue=zzTraceOptionValue;
    zzTraceOptionValue=buf->traceOptionValue;
    if ( (prevTraceOptionValue > 0) !=
             (zzTraceOptionValue > 0)) {
      if (zzTraceOptionValue > 0) {
        fprintf(stderr,"trace enable restored in rule %s depth %d\n",
                        zzTraceCurrentRuleName,zzTraceDepth);
      };
      if (zzTraceOptionValue <= 0) {
        fprintf(stderr,"trace disable restored in rule %s depth %d\n",
                        zzTraceCurrentRuleName,zzTraceDepth);
      };
    };

    zzTraceOptionValue=buf->traceOptionValue;            /* MR10 */
    zzTraceGuessOptionValue=buf->traceGuessOptionValue;  /* MR10 */
    zzTraceCurrentRuleName=buf->traceCurrentRuleName;    /* MR10 */
    zzTraceDepth=buf->traceDepth;                        /* MR10 */
    zzTraceGuessDone(buf);                               /* MR10 */
#endif
}

void
#ifdef __USE_PROTOS
zzedecode(SetWordType *a)
#else
zzedecode(a)
SetWordType *a;
#endif
{
	register SetWordType *p = a;
	register SetWordType *endp = &(p[zzSET_SIZE]);
	register unsigned e = 0;

	if ( zzset_deg(a)>1 ) fprintf(stderr, " {");
	do {
		register SetWordType t = *p;
		register SetWordType *b = &(bitmask[0]);
		do {
			if ( t & *b ) fprintf(stderr, " %s", zztokens[e]);
			e++;
		} while (++b < &(bitmask[sizeof(SetWordType)*8]));
	} while (++p < endp);
	if ( zzset_deg(a)>1 ) fprintf(stderr, " }");
}

#ifndef USER_ZZSYN
/* standard error reporting function */
void
#ifdef __USE_PROTOS
zzsyn(char *text, int tok, char *egroup, SetWordType *eset, int etok, int k, char *bad_text)
#else
zzsyn(text, tok, egroup, eset, etok, k, bad_text)
char *text, *egroup, *bad_text;
int tok;
int etok;
int k;
SetWordType *eset;
#endif
{
	
    zzSyntaxErrCount++;                             /* MR11 */
	fprintf(stderr, "line %d: syntax error at \"%s\"", zzline, (tok==zzEOF_TOKEN)?"EOF":bad_text);
	if ( !etok && !eset ) {fprintf(stderr, "\n"); return;}
	if ( k==1 ) fprintf(stderr, " missing");
	else
	{
		fprintf(stderr, "; \"%s\" not", bad_text);
		if ( zzset_deg(eset)>1 ) fprintf(stderr, " in");
	}
	if ( zzset_deg(eset)>0 ) zzedecode(eset);
	else fprintf(stderr, " %s", zztokens[etok]);
	if ( strlen(egroup) > 0 ) fprintf(stderr, " in %s", egroup);
	fprintf(stderr, "\n");
}
#endif

/* is b an element of set p? */
int
#ifdef __USE_PROTOS
zzset_el(unsigned b, SetWordType *p)
#else
zzset_el(b,p)
unsigned b;
SetWordType *p;
#endif
{
	return( p[BSETDIVWORD(b)] & bitmask[BSETMODWORD(b)] );
}

int
#ifdef __USE_PROTOS
zzset_deg(SetWordType *a)
#else
zzset_deg(a)
SetWordType *a;
#endif
{
	/* Fast compute degree of a set... the number
	   of elements present in the set.  Assumes
	   that all word bits are used in the set
	*/
	register SetWordType *p = a;
	register SetWordType *endp = &(a[zzSET_SIZE]);
	register int degree = 0;

	if ( a == NULL ) return 0;
	while ( p < endp )
	{
		register SetWordType t = *p;
		register SetWordType *b = &(bitmask[0]);
		do {
			if (t & *b) ++degree;
		} while (++b < &(bitmask[sizeof(SetWordType)*8]));
		p++;
	}

	return(degree);
}

#ifdef DEMAND_LOOK

#ifdef LL_K
int
#ifdef __USE_PROTOS
_zzmatch(int _t, char **zzBadText, char **zzMissText,
		int *zzMissTok, int *zzBadTok,
		SetWordType **zzMissSet)
#else
_zzmatch(_t, zzBadText, zzMissText, zzMissTok, zzBadTok, zzMissSet)
int _t;
char **zzBadText;
char **zzMissText;
int *zzMissTok, *zzBadTok;
SetWordType **zzMissSet;
#endif
{
	if ( zzdirty==LL_K ) {
		zzCONSUME;
	}
	if ( LA(1)!=_t ) {
		*zzBadText = *zzMissText=LATEXT(1);	
		*zzMissTok= _t; *zzBadTok=LA(1);
		*zzMissSet=NULL;				
		return 0;
	}
	zzMakeAttr						
	zzdirty++;						
	zzlabase++;						
	return 1;
}

int
#ifdef __USE_PROTOS
_zzmatch_wsig(int _t)
#else
_zzmatch_wsig(_t)
int _t;
#endif
{
	if ( zzdirty==LL_K ) {
		zzCONSUME;
	}
	if ( LA(1)!=_t ) {
		return 0;
	}
	zzMakeAttr						
	zzdirty++;						
	zzlabase++;						
	return 1;
}

#else

int
#ifdef __USE_PROTOS
_zzmatch(int _t, char **zzBadText, char **zzMissText,
		 int *zzMissTok, int *zzBadTok, SetWordType **zzMissSet)
#else
_zzmatch(_t, zzBadText, zzMissText, zzMissTok, zzBadTok, zzMissSet)
int _t;
char **zzBadText;
char **zzMissText;
int *zzMissTok, *zzBadTok;
SetWordType **zzMissSet;
#endif
{								
	if ( zzdirty ) {zzCONSUME;}		
	if ( LA(1)!=_t ) {
		*zzBadText = *zzMissText=LATEXT(1);	
		*zzMissTok= _t; *zzBadTok=LA(1);
		*zzMissSet=NULL;				
		return 0;
	}								
	zzdirty = 1;					
	zzMakeAttr						
	return 1;
}

int
#ifdef __USE_PROTOS
_zzmatch_wsig(int _t)
#else
_zzmatch_wsig(_t)
int _t;
#endif
{
	if ( zzdirty ) {zzCONSUME;}		
	if ( LA(1)!=_t ) {
		return 0;
	}
	zzdirty = 1;					
	zzMakeAttr						
	return 1;
}

#endif /*LL_K*/

#else

int
#ifdef __USE_PROTOS
_zzmatch(int _t, char **zzBadText, char **zzMissText,
		int *zzMissTok, int *zzBadTok,
		SetWordType **zzMissSet)
#else
_zzmatch(_t, zzBadText, zzMissText, zzMissTok, zzBadTok, zzMissSet)
int _t;
char **zzBadText;
char **zzMissText;
int *zzMissTok, *zzBadTok;
SetWordType **zzMissSet;
#endif
{
	if ( LA(1)!=_t ) {				
		*zzBadText = *zzMissText=LATEXT(1);	
		*zzMissTok= _t; *zzBadTok=LA(1);
		*zzMissSet=NULL;				
		return 0;
	}
	zzMakeAttr
	return 1;
}

int
#ifdef __USE_PROTOS
_zzmatch_wsig(int _t)
#else
_zzmatch_wsig(_t)
int _t;
#endif
{
	if ( LA(1)!=_t ) return 0;
	zzMakeAttr						
	return 1;
}

#endif /*DEMAND_LOOK*/

#ifdef ZZINF_LOOK
void
#ifdef __USE_PROTOS
_inf_zzgettok(void)
#else
_inf_zzgettok()
#endif
{
	if ( zzinf_labase >= zzinf_last )					
		{NLA = zzEOF_TOKEN; strcpy(NLATEXT, "");}	
	else {											
		NLA = zzinf_tokens[zzinf_labase];
		zzline = zzinf_line[zzinf_labase];	/* wrong in 1.21 */
		strcpy(NLATEXT, zzinf_text[zzinf_labase]);		
		zzinf_labase++; 								
	}												
}
#endif

#ifdef ZZINF_LOOK
/* allocate default size text,token and line arrays;
 * then, read all of the input reallocing the arrays as needed.
 * Once the number of total tokens is known, the LATEXT(i) array (zzinf_text)
 * is allocated and it's pointers are set to the tokens in zzinf_text_buffer.
 */
void
#ifdef __USE_PROTOS
zzfill_inf_look(void)
#else
zzfill_inf_look()
#endif
{
	int tok, line;
	int zzinf_token_buffer_size = ZZINF_DEF_TOKEN_BUFFER_SIZE;
	int zzinf_text_buffer_size = ZZINF_DEF_TEXT_BUFFER_SIZE;
	int zzinf_text_buffer_index = 0;
	int zzinf_lap = 0;

	/* allocate text/token buffers */
	zzinf_text_buffer = (char *) malloc(zzinf_text_buffer_size);
	if ( zzinf_text_buffer == NULL )
	{
		fprintf(stderr, "cannot allocate lookahead text buffer (%d bytes)\n",
		zzinf_text_buffer_size);
		exit(PCCTS_EXIT_FAILURE);									
	}
	zzinf_tokens = (int *) calloc(zzinf_token_buffer_size,sizeof(int));
	if ( zzinf_tokens == NULL )
	{
		fprintf(stderr,	"cannot allocate token buffer (%d tokens)\n",
				zzinf_token_buffer_size);
		exit(PCCTS_EXIT_FAILURE);									
	}
    zzinf_line = (int *) calloc(zzinf_token_buffer_size,sizeof(int));
    if ( zzinf_line == NULL )
    {
        fprintf(stderr, "cannot allocate line buffer (%d ints)\n",
                zzinf_token_buffer_size);
        exit(PCCTS_EXIT_FAILURE);
	}

	/* get tokens, copying text to text buffer */
	zzinf_text_buffer_index = 0;
	do {
		zzgettok();
		line = zzreal_line;
		while ( zzinf_lap>=zzinf_token_buffer_size )
		{
			zzinf_token_buffer_size += ZZINF_BUFFER_TOKEN_CHUNK_SIZE;
			zzinf_tokens = (int *) realloc(zzinf_tokens,
												 zzinf_token_buffer_size*sizeof(int));
			if ( zzinf_tokens == NULL )
			{
				fprintf(stderr, "cannot allocate lookahead token buffer (%d tokens)\n",
						zzinf_token_buffer_size);
				exit(PCCTS_EXIT_FAILURE);
			}
            zzinf_line = (int *) realloc(zzinf_line,
                                         zzinf_token_buffer_size*sizeof(int));
            if ( zzinf_line == NULL )
            {
                fprintf(stderr, "cannot allocate lookahead line buffer (%d ints)\n",
                        zzinf_token_buffer_size);
                exit(PCCTS_EXIT_FAILURE);
			}

		}
		while ( (zzinf_text_buffer_index+strlen(NLATEXT)+1) >= zzinf_text_buffer_size )
		{
			zzinf_text_buffer_size += ZZINF_BUFFER_TEXT_CHUNK_SIZE;
			zzinf_text_buffer = (char *) realloc(zzinf_text_buffer,
												 zzinf_text_buffer_size);
			if ( zzinf_text_buffer == NULL )
			{
				fprintf(stderr,	"cannot allocate lookahead text buffer (%d bytes)\n",
						zzinf_text_buffer_size);
				exit(PCCTS_EXIT_FAILURE);
			}
		}
		/* record token and text and line of input symbol */
		tok = zzinf_tokens[zzinf_lap] = NLA;
		strcpy(&zzinf_text_buffer[zzinf_text_buffer_index], NLATEXT);
		zzinf_text_buffer_index += strlen(NLATEXT)+1;
        zzinf_line[zzinf_lap] = line;
		zzinf_lap++;
	} while (tok!=zzEOF_TOKEN);
	zzinf_labase = 0;
	zzinf_last = zzinf_lap-1;

	/* allocate ptrs to text of ith token */
	zzinf_text = (char **) calloc(zzinf_last+1,sizeof(char *));
	if ( zzinf_text == NULL )
	{
		fprintf(stderr,	"cannot allocate lookahead text buffer (%d)\n",
				zzinf_text_buffer_size);
		exit(PCCTS_EXIT_FAILURE);										
	}													
	zzinf_text_buffer_index = 0;
	zzinf_lap = 0;
	/* set ptrs so that zzinf_text[i] is the text of the ith token found on input */
	while (zzinf_lap<=zzinf_last)
	{
	    zzinf_text[zzinf_lap++] = &zzinf_text_buffer[zzinf_text_buffer_index];
		zzinf_text_buffer_index += strlen(&zzinf_text_buffer[zzinf_text_buffer_index])+1;
	}
}
#endif

int
#ifdef __USE_PROTOS
_zzsetmatch(SetWordType *e, char **zzBadText, char **zzMissText,
			int *zzMissTok, int *zzBadTok,
			SetWordType **zzMissSet,
			SetWordType *zzTokclassErrset /* MR23 */)
#else
_zzsetmatch(e, zzBadText, zzMissText, zzMissTok, zzBadTok, zzMissSet, zzTokclassErrset /* MR23 */)
SetWordType *e;
char **zzBadText;
char **zzMissText;
int *zzMissTok, *zzBadTok;
SetWordType **zzMissSet;
SetWordType *zzTokclassErrset;
#endif
{
#ifdef DEMAND_LOOK
#ifdef LL_K
	if ( zzdirty==LL_K ) {zzCONSUME;}
#else
	if ( zzdirty ) {zzCONSUME;}
#endif
#endif
	if ( !zzset_el((unsigned)LA(1), e) ) {
		*zzBadText = LATEXT(1); *zzMissText=NULL;
		*zzMissTok= 0; *zzBadTok=LA(1);
		*zzMissSet=zzTokclassErrset; /* MR23 */
		return 0;
	}
	zzMakeAttr           /* MR14 Ger Hobbelt (hobbelt@axa.nl) */
#ifdef DEMAND_LOOK
#ifdef LL_K
	zzdirty++;
    zzlabase++;          /* MR14 Ger Hobbelt (hobbelt@axa.nl) */
#else
	zzdirty = 1;
#endif
#endif
	return 1;
}

int
#ifdef __USE_PROTOS
_zzmatch_wdfltsig(int tokenWanted, SetWordType *whatFollows)
#else
_zzmatch_wdfltsig(tokenWanted, whatFollows)
int tokenWanted;
SetWordType *whatFollows;
#endif
{
#ifdef DEMAND_LOOK
#ifdef LL_K
	if ( zzdirty==LL_K ) {
			zzCONSUME;
	}
#else
	if ( zzdirty ) {zzCONSUME;}
#endif
#endif

	if ( LA(1)!=tokenWanted )
	{
        zzSyntaxErrCount++;     /* MR11 */
		fprintf(stderr,
				"line %d: syntax error at \"%s\" missing %s\n",
				zzline,
				(LA(1)==zzEOF_TOKEN)?"<eof>":(char *)LATEXT(1),
				zztokens[tokenWanted]);
		zzconsumeUntil( whatFollows );
		return 0;
	}
	else {
		zzMakeAttr						
#ifdef DEMAND_LOOK
#ifdef LL_K
		zzdirty++;
		zzlabase++;
#else
		zzdirty = 1;
#endif
#else
/*		zzCONSUME;		 consume if not demand lookahead */
#endif
		return 1;
	}
}

int
#ifdef __USE_PROTOS
_zzsetmatch_wdfltsig(SetWordType *tokensWanted,
					 int tokenTypeOfSet,
					 SetWordType *whatFollows)
#else
_zzsetmatch_wdfltsig(tokensWanted, tokenTypeOfSet, whatFollows)
SetWordType *tokensWanted;
int tokenTypeOfSet;
SetWordType *whatFollows;
#endif
{
#ifdef DEMAND_LOOK
#ifdef LL_K
	if ( zzdirty==LL_K ) {zzCONSUME;}
#else
	if ( zzdirty ) {zzCONSUME;}
#endif
#endif
	if ( !zzset_el((unsigned)LA(1), tokensWanted) )
	{
        zzSyntaxErrCount++;     /* MR11 */
		fprintf(stderr,
				"line %d: syntax error at \"%s\" missing %s\n",
				zzline,
				(LA(1)==zzEOF_TOKEN)?"<eof>":(char *)LATEXT(1),
				zztokens[tokenTypeOfSet]);
		zzconsumeUntil( whatFollows );
		return 0;
	}
	else {
		zzMakeAttr
#ifdef DEMAND_LOOK
#ifdef LL_K
		zzdirty++;
		zzlabase++;
#else
		zzdirty = 1;
#endif
#else
/*		zzCONSUME;		consume if not demand lookahead */
#endif
		return 1;
	}
}

int
#ifdef __USE_PROTOS
_zzsetmatch_wsig(SetWordType *e)
#else
_zzsetmatch_wsig(e)
SetWordType *e;
#endif
{
#ifdef DEMAND_LOOK
#ifdef LL_K
	if ( zzdirty==LL_K ) {zzCONSUME;}
#else
	if ( zzdirty ) {zzCONSUME;}
#endif
#endif
	if ( !zzset_el((unsigned)LA(1), e) ) return 0;
	zzMakeAttr           /* MR14 Ger Hobbelt (hobbelt@axa.nl) */
#ifdef DEMAND_LOOK
#ifdef LL_K
	zzdirty++;
    zzlabase++;          /* MR14 Ger Hobbelt (hobbelt@axa.nl) */
#else
	zzdirty = 1;
#endif
#endif
	return 1;
}

#ifdef USER_ZZMODE_STACK
static int  zzmstk[ZZMAXSTK] = { -1 };
static int  zzmdep = 0;
static char zzmbuf[70];

void
#ifdef __USE_PROTOS
zzmpush( int m )
#else
zzmpush( m )
int m;
#endif
{
   if(zzmdep == ZZMAXSTK - 1) {
     sprintf(zzmbuf, "Mode stack overflow ");
     zzerr(zzmbuf);
   } else {
     zzmstk[zzmdep++] = zzauto;
     zzmode(m);
   }
}

void
#ifdef __USE_PROTOS
zzmpop( void )
#else
zzmpop( )
#endif
{
   if(zzmdep == 0)
   {  sprintf(zzmbuf, "Mode stack underflow ");
      zzerr(zzmbuf);
   }
   else
   {  zzmdep--;
      zzmode(zzmstk[zzmdep]);
   }
}

void
#ifdef __USE_PROTOS
zzsave_mode_stack( int modeStack[], int *modeLevel )
#else
zzsave_mode_stack( modeStack, modeLevel )
int modeStack[];
int *modeLevel;
#endif
{
  int i;
  memcpy(modeStack, zzmstk, sizeof(zzmstk));
  *modeLevel = zzmdep;
  zzmdep = 0;

  return;
}

void
#ifdef __USE_PROTOS
zzrestore_mode_stack( int modeStack[], int *modeLevel )
#else
zzrestore_mode_stack( modeStack, modeLevel )
int modeStack[];
int *modeLevel;
#endif
{
  int i;

  memcpy(zzmstk, modeStack, sizeof(zzmstk));
  zzmdep = *modeLevel;

  return;
}
#endif /* USER_ZZMODE_STACK */

#ifdef __USE_PROTOS
void zzTraceReset(void)
#else
void zzTraceReset()
#endif
{
#ifdef zzTRACE_RULES
  zzTraceOptionValue=zzTraceOptionValueDefault;
  zzTraceGuessOptionValue=1;
  zzTraceCurrentRuleName=NULL;
  zzTraceDepth=0;
#endif
}

#ifdef __USE_PROTOS
void zzTraceGuessFail(void)
#else
void zzTraceGuessFail()
#endif
{

#ifdef zzTRACE_RULES
#ifdef ZZCAN_GUESS

  int   doIt=0;

  if (zzTraceOptionValue <= 0) {
    doIt=0;
  } else if (zzguessing && zzTraceGuessOptionValue <= 0) {
    doIt=0;
  } else {
    doIt=1;
  };

  if (doIt) {
    fprintf(stderr,"guess failed\n");
  };
#endif
#endif
}

/* zzTraceOption:
     zero value turns off trace
*/

#ifdef __USE_PROTOS
void zzTraceIn(char * rule)
#else
void zzTraceIn(rule)
  char  *rule;
#endif
{
#ifdef zzTRACE_RULES

  int           doIt=0;

  zzTraceDepth++;
  zzTraceCurrentRuleName=rule;

  if (zzTraceOptionValue <= 0) {
    doIt=0;
#ifdef ZZCAN_GUESS
  } else if (zzguessing && zzTraceGuessOptionValue <= 0) {
    doIt=0;
#endif
  } else {
    doIt=1;
  };

  if (doIt) {
    fprintf(stderr,"enter rule %s {\"%s\"} depth %d",
            rule,
            LA(1)==1 ? "@" : (char *) LATEXT(1),    /* MR19 */
            zzTraceDepth);
#ifdef ZZCAN_GUESS
    if (zzguessing) fprintf(stderr," guessing");
#endif
    fprintf(stderr,"\n");
  };
#endif
  return;
}

#ifdef __USE_PROTOS
void zzTraceOut(char * rule)
#else
void zzTraceOut(rule)
  char  *rule;
#endif
{
#ifdef zzTRACE_RULES
  int       doIt=0;

  zzTraceDepth--;

  if (zzTraceOptionValue <= 0) {
    doIt=0;
#ifdef ZZCAN_GUESS
  } else if (zzguessing && zzTraceGuessOptionValue <= 0) {
    doIt=0;
#endif
  } else {
    doIt=1;
  };

  if (doIt) {
    fprintf(stderr,"exit rule %s {\"%s\"} depth %d",
            rule,
            LA(1)==1 ? "@" : (char *) LATEXT(1), /* MR19 */
            zzTraceDepth+1);
#ifdef ZZCAN_GUESS
    if (zzguessing) fprintf(stderr," guessing");
#endif
    fprintf(stderr,"\n");
  };
#endif
}

#ifdef __USE_PROTOS
int zzTraceOption(int delta)
#else
int zzTraceOption(delta)
  int   delta;
#endif
{
#ifdef zzTRACE_RULES
    int     prevValue=zzTraceOptionValue;

    zzTraceOptionValue=zzTraceOptionValue+delta;

    if (zzTraceCurrentRuleName != NULL) {
      if (prevValue <= 0 && zzTraceOptionValue > 0) {
        fprintf(stderr,"trace enabled in rule %s depth %d\n",
                                            zzTraceCurrentRuleName,zzTraceDepth);
      };
      if (prevValue > 0 && zzTraceOptionValue <= 0) {
        fprintf(stderr,"trace disabled in rule %s depth %d\n",
                                            zzTraceCurrentRuleName,zzTraceDepth);
      };
    };
    return  prevValue;
#else
    return 0;
#endif
}

#ifdef __USE_PROTOS
int zzTraceGuessOption(int delta)
#else
int zzTraceGuessOption(delta)
  int   delta;
#endif
{
#ifdef zzTRACE_RULES
#ifdef ZZCAN_GUESS
    int     prevValue=zzTraceGuessOptionValue;

    zzTraceGuessOptionValue=zzTraceGuessOptionValue+delta;

    if (zzTraceCurrentRuleName != NULL) {
      if (prevValue <= 0 && zzTraceGuessOptionValue > 0) {
        fprintf(stderr,"guess trace enabled in rule %s depth %d\n",
                                                zzTraceCurrentRuleName,zzTraceDepth);
      };
      if (prevValue > 0 && zzTraceGuessOptionValue <= 0) {
        fprintf(stderr,"guess trace disabled in rule %s depth %d\n",
                                                zzTraceCurrentRuleName,zzTraceDepth);
      };
    };
    return prevValue;
#else
    return 0;
#endif
#else
    return 0;
#endif
}

#endif /* ERR_H */
