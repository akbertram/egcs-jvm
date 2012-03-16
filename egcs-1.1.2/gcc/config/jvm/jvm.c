/*!**************************************************************************
*!
*! FILE NAME : aux-output.c
*!
*! CONTAINS  : Support routines for the Jvm port of GCC.
*!
*!             const_ref_operand     predicate for match_operand
*!             bdap_operand          predicate for match_operator
*!             bdap_biap_operand     predicate for match_operator
*!             orthogonal_operator   predicate for match_operator
*!             commutative_orth_op   predicate for match_operator
*!             operand_extend_operator      predicate for match_operator
*!             extend_operator       predicate for match_operator
*!             plus_or_bound_operator       predicate for match_operator
*!
*!             op_str                used in the output section
*!                                   of a define_insn
*!             function_prologue     assembler to file for ...
*!             save_regs_mentioned   checks an insn to see if reg 0..8
*!                                   are mentioned.
*!             eligible_for_epilogue_delay Return true if the insn may
*!                                   be put in the delay in the epilogue.
*!             delay_slots_for_epilogue  Return 1 if epilogue contains
*!                                   "ret", else 0
*!             function_epilogue     assembler to file for ...
*!             print_operand         print assembler operand
*!             print_operand_address print assembler operand address
*!             initial_fp_sp_offset  check what to add to sp to get to
*!                                   same stack location as fp would have got.
*!             notice_update_cc      checks an insns change of cc and updates
*!             simple_epilogue       checks if "ret" or "jump [sp+]"
*!                                   may be used instead of jumping to the
*!                                   function epilogue.
*!             jvm_address_cost     returns the cost of an adressing mode
*!             side_effect_mode_ok   finds out if the operands allow a
*!                                   side-effect addressing mode.
*!             same_ref_as_saved     checks a bit extra for possible cse.
*!             get_real_related_value like get_related_value but no bug.
*!             redundant             a try to remove redundant "test" insns.
*!             output_block_move     output move instructions for block
*!             adjust_ops            fix to change VOIDmode into
*!                                   SImode for regs.
*!             debug_printf          for debug printouts
*!             override_options      for TARGET_OPTIONS processing.
*!
*!
*!
*!  And other assorted junk that I've thrown in here - tw.
*!--------------------------------------------------------------------------
*!
*!
*!***************************************************************************/

/****************************************************************************
This file is part of GNU CC.

GNU CC is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 1, or (at your option)
any later version.

GNU CC is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with GNU CC; see the file COPYING.  If not, write to
the Free Software Foundation, 675 Mass Ave, Cambridge, MA 02139, USA. 
*****************************************************************************/

/********* MACRO SECTION **********/
#define STR_HASHSIZE_MAX 1009       /* Snatch from 2.7.2::varasm.c */

/********* INCLUDE FILES SECTION **********/

#include <stdio.h>
#include <stdlib.h>
#include "config.h"
#include "rtl.h"
#include "regs.h"
#include "hard-reg-set.h"
#include "real.h"
#include "insn-config.h"
#include "conditions.h"
#include "insn-flags.h"
#include "output.h"
#include "insn-attr.h"
#include "tree.h"
#include "insn-codes.h"

#if 0
/* Why not?  Does not work? */
#include "gvarargs.h"
#endif

/* EXTERN FUNCTIONS */
extern int get_frame_size();
extern int reg_mentioned_p ();
extern rtx final_scan_insn ();
extern void fatal();
/*extern int dbr_sequence_length ();*/
extern int reg_overlap_mentioned_p ();
extern int sets_cc0_p ();
extern int rtx_equal_p ();
extern int register_operand();
extern void debug_rtx();
extern void output_address();
extern void output_addr_const();

/* externs */
extern int frame_pointer_needed;
/* statics */
static int size_of_addr_mode;

/********** TYPE DEFINITIONS *************/
struct deferred_string_struct_type
{
  int labelno;
  char *str;
  int str_len;
  int output_it;
  struct deferred_string_struct_type *next;
};

/********** LOCAL VARIABLES *************/
static struct deferred_string_struct_type
deferred_strings[STR_HASHSIZE_MAX];

/********** GLOBAL VARIABLES *************/

int first_vararg_reg; /* In functions that uses varargs or stdarg
			 (anonymous arguments), the first register
			 with an anonymous argument is this.
		       */

rtx final_saved_insn;		/* Reduce braindamage in cse. */

rtx same_ref_as_saved(); /* Extra cse for address expressions. */
static rtx get_real_related_value();	/* Like get_related_value, but accept 
					   label_ref  && symbol_ref. */
static int my_reg_overlap_mentioned_p (); /* Fix for reg_overlap_mentioned_p() */


/* Unused constant string removal support */
char my_inhibit_stringout = 0;  /* Don't ASM_OUTPUT_ASCII if == 1 */

char my_string_label_referenced = 0; /* STRIP_NAME_ENCODING is in a
                                        reference (asm or pseudo op)
                                        if == 1 */

/* Used to keep track of the name of the current function
   (current_function_name is not valid at assembly output time). */
char *my_current_function_name = NULL;

char *my_class_name = NULL;

char *jvm_max_stackframe_str;
int jvm_max_stackframe = 0;

/************************** --- FUNCTIONS --- ****************************/

void printasmstart(file,name) 
  FILE *file;
  char *name;
{
  char *p;
  
  my_class_name = xstrdup(name);
  p = strrchr(my_class_name,'.');
  if (p) *p=0;
  my_class_name[0]&=~0x20; 
/*  fprintf(file, ".class public %s\n" 
                ".super TranslatedFile\n\n" 
                ".method public <init>()V\n" 
		"\t.limit stack 5\n"          
                "\t.limit locals 16\n\n" 
		"\taload_0\n" 
                "\tinvokenonvirtual TranslatedFile/<init>()V\n" 
                "\treturn\n" 
		".end method\n\n" 
                ".method public static main([Ljava/lang/String;)V\n" 
                "\t.limit stack 5\n"
		"\t.limit locals 16\n\n" 
                "\tnew %s\n"
		"\tdup\n" 
                "\tinvokespecial %s/<init>()V\n" 
                "\taload_0\n" 
                "\tinvokevirtual %s/Realmain([Ljava/lang/String;)V\n" 
                "\treturn\n" 
                ".end method\n\n" 
  ,my_class_name,my_class_name,my_class_name,my_class_name); */
}

/****************************** PREDICATES ******************************/
/*#**************************************************************************
*#
*#  FUNCTION NAME : const_ref_operand
*#
*#  PARAMETERS    : op    an operand to be tested
*#                  mode  supposed machine mode of the operand
*#
*#  RETURNS       : 1 or 0 (predicate)
*#
*#  DESCRIPTION   : Checks to see if OP is either 
*#                  a) a valid assembly-time constant, or
*#                  b) a valid assembly-time-constant plus a literal
*#                     constant
*#                  Returns 1 if this is the case, else 0.
*#                  Intended for use as a predicate to match_operand.
*#
*#---------------------------------------------------------------------------
*#
*#  HISTORY
*#
*#  DATE     NAME                  CHANGES
*#  ----     ----                  -------
*#  920730   HP                    Initial
*#************************************************************************#*/
int
const_ref_operand(op, mode)
register rtx op;
enum machine_mode mode;
{
  register enum rtx_code code;

  /* This function is not only used as a predicate. */
  if (op == 0)
    return 0;

  code = GET_CODE(op);

  if (mode == VOIDmode)
    mode = GET_MODE(op);

  /* Dont allow large operands. */
  if (GET_MODE_SIZE(mode) > UNITS_PER_WORD)
    return 0;

  return (code == LABEL_REF || code == SYMBOL_REF
	  || (code == CONST && GET_CODE(XEXP(op,0)) == PLUS
	      && GET_CODE(XEXP(XEXP(op,0),1)) == CONST_INT
	      && (GET_CODE(XEXP(XEXP(op,0),0)) == LABEL_REF
		  || GET_CODE(XEXP(XEXP(op,0),0)) == SYMBOL_REF)));
}

/*#**************************************************************************
*#
*#  FUNCTION NAME : bdap_operand
*#
*#  PARAMETERS    : op    an operand to be tested
*#                  mode  supposed machine mode of the operand
*#
*#  RETURNS       : 1 or 0 (predicate)
*#
*#  DESCRIPTION   : Checks to see if OP is either 
*#                  a) a register
*#                  b) a CONST operand
*#                  c) a [r] or [r+] in SImode, or sign-extend from HI or QI
*#                  Intended for use as a predicate to match_operand.
*#
*#---------------------------------------------------------------------------
*#
*#  HISTORY
*#
*#  DATE     NAME                  CHANGES
*#  ----     ----                  -------
*#  930513   HP                    initial, from bdap_biap_operand
*#************************************************************************#*/
int
bdap_operand(op, mode)
register rtx op;
enum machine_mode mode;
{
  register enum rtx_code code = GET_CODE(op);
  
  if (mode != SImode && (mode != VOIDmode || GET_MODE(op) != VOIDmode))
    return 0;
  
  /* Just return is this is a simple register.  */
  if (register_operand(op,mode))
    return 1;
  
  /* Const? */
  if (CONSTANT_P(op))
    return 1;
  else
    /* [r] or [r+]? */
    if (code == MEM) {
      rtx tem = XEXP(op,0);
      if (mode == SImode
	  && (register_operand(tem,SImode)
	      || (GET_CODE(tem) == POST_INC
		  && register_operand(XEXP(tem,0),SImode))))	  
	return 1;
      else 
	return 0;
    }
    else
      /* [r].bw or [r+].bw */
      if (code == SIGN_EXTEND) {
	rtx tem = XEXP(op,0);
	if (GET_CODE(tem) != MEM)
	  return 0;
	tem = XEXP(tem,0);
	if (mode == SImode
	    && (register_operand(tem,SImode)
		|| (GET_CODE(tem) == POST_INC
		    && register_operand(XEXP(tem,0),SImode))))
	  return 1;
	return 0;
      }
      else
	/* fail */
	return 0;
}

/*#**************************************************************************
*#
*#  FUNCTION NAME : bdap_biap_operand
*#
*#  PARAMETERS    : op    an operand to be tested
*#                  mode  supposed machine mode of the operand
*#
*#  RETURNS       : 1 or 0 (predicate)
*#
*#  DESCRIPTION   : Checks to see if OP is either 
*#                  a) a register
*#                  b) a CONST operand
*#                  c) a mult of (1, 2 or 4) and a register
*#                  d) a [r] or [r+] in SImode, or sign-extend from HI or QI
*#                  Intended for use as a predicate to match_operand.
*#                    CURRENTLY ONLY USED IN PEEPHOLE OPTIMIZATION.
*#
*#---------------------------------------------------------------------------
*#
*#  HISTORY
*#
*#  DATE     NAME                  CHANGES
*#  ----     ----                  -------
*#  920715   HP                    initial
*#************************************************************************#*/
int
bdap_biap_operand(op, mode)
register rtx op;
enum machine_mode mode;
{
  register enum rtx_code code = GET_CODE(op);
  rtx reg;
  rtx val;
  
  if (mode != SImode && (mode != VOIDmode || GET_MODE(op) != VOIDmode))
    return 0;
  
  /* Just return is this is a simple register.  */
  if (register_operand(op,mode))
    return 1;
  
  /* Shifting operator? Else bdap operator  */
  if (code != MULT /*  && code != LSHIFT && code != ASHIFT */) {
    /* Bdap operator */
    
    /* Const? */
    if (CONSTANT_P(op))
      return 1;
    else
      /* [r] or [r+]? */
      if (code == MEM) {
	rtx tem = XEXP(op,0);
	if (mode == SImode
	    && (register_operand(tem,SImode)
		|| (GET_CODE(tem) == POST_INC
		    && register_operand(XEXP(tem,0),SImode))))	  
	  return 1;
	else 
	  return 0;
      }
    else
      /* [r].bw or [r+].bw */
      if (code == SIGN_EXTEND) {
	rtx tem = XEXP(op,0);
	if (GET_CODE(tem) != MEM)
	  return 0;
	tem = XEXP(tem,0);
	if (mode == SImode
	    && (register_operand(tem,SImode)
		|| (GET_CODE(tem) == POST_INC
		    && register_operand(XEXP(tem,0),SImode))))
	  return 1;
	return 0;
      }
    else
      /* fail */
      return 0;
  }

  /* Canonicalize reg && shiftval */
  if (GET_CODE(XEXP(op,0)) == CONST_INT) {
    val = XEXP(op,0);
    reg = XEXP(op,1);
  } else {
    val = XEXP(op,1);
    reg = XEXP(op,0);
  }
  
  /* Check that the members of the canonicalized order are correct.  */
  if (!register_operand(reg,SImode) || GET_CODE(val) != CONST_INT)
    return 0;
  
  /* Check that the numbers of val are correct.  */
  if ((code == MULT
       && (INTVAL(val) == 1 || INTVAL(val) == 2 || INTVAL(val) == 4))
      /* || (INTVAL(val) == 0 || INTVAL(val) == 1 || INTVAL(val) == 2) */)
    return 1;
  return 0;
}

/*#**************************************************************************
*#
*#  FUNCTION NAME : orthogonal_operator
*#
*#  PARAMETERS    : x      rtx operation to be tested
*#                  mode   supposed mode of the operation
*#
*#  RETURNS       : 1 or 0 (predicate)
*#
*#  DESCRIPTION   : Check to see if MODE is same as mode for X, 
*#                  and X is PLUS, MINUS, IOR or AND or UMIN.
*#                  Return 1 if so, else 0.
*#                  Intended as a predicate for match_operator.
*#
*#---------------------------------------------------------------------------
*#
*#  HISTORY
*#
*#  DATE     NAME                  CHANGES
*#  ----     ----                  -------
*#  911106   RW                    Initial
*#  911217   RW                    XOR removed (only has register addr. mode)
*#
*#************************************************************************#*/
int
orthogonal_operator(x, mode)
rtx x;
enum machine_mode mode;
{
  enum rtx_code code = GET_CODE(x);

  if (mode == VOIDmode)
    mode = GET_MODE(x);

  return (GET_MODE(x) == mode &&
          (code == PLUS || code == MINUS
	   || code == IOR || code == AND || code == UMIN));
}

/*#**************************************************************************
*#
*#  FUNCTION NAME : commutative_orth_op
*#
*#  PARAMETERS    : x      rtx operation to be tested
*#                  mode   supposed mode of the operation
*#
*#  RETURNS       : 1 or 0 (predicate)
*#
*#  DESCRIPTION   : Check to see if MODE is same as mode for X, 
*#                  and X is PLUS, IOR or AND or UMIN.
*#                  Return 1 if so, else 0.
*#                  Intended as a predicate for match_operator.
*#
*#---------------------------------------------------------------------------
*#
*#  HISTORY
*#
*#  DATE     NAME                  CHANGES
*#  ----     ----                  -------
*#  920721   HP                    initial
*#
*#************************************************************************#*/
int
commutative_orth_op(x, mode)
rtx x;
enum machine_mode mode;
{
  enum rtx_code code = GET_CODE(x);

  if (mode == VOIDmode)
    mode = GET_MODE(x);

  return (GET_MODE(x) == mode &&
          (code == PLUS
	   || code == IOR || code == AND || code == UMIN));
}

/*#**************************************************************************
*#
*#  FUNCTION NAME : operand_extend_operator
*#
*#  PARAMETERS    : x      rtx operation to be tested
*#                  mode   supposed mode of the operation
*#
*#  RETURNS       : 1 or 0 (predicate)
*#
*#  DESCRIPTION   : Check to see if MODE is same as mode for X, 
*#                  and X is PLUS or MINUS or UMIN
*#                  Return 1 if so, else 0.
*#                  Intended as a predicate for match_operator.
*#
*#---------------------------------------------------------------------------
*#
*#  HISTORY
*#
*#  DATE     NAME                  CHANGES
*#  ----     ----                  -------
*#  920721   HP                    initial
*#
*#************************************************************************#*/
int
operand_extend_operator(x, mode)
rtx x;
enum machine_mode mode;
{
  enum rtx_code code = GET_CODE(x);

  if (mode == VOIDmode)
    mode = GET_MODE(x);

  return (GET_MODE(x) == mode &&
          (code == PLUS || code == MINUS || code == UMIN));
}

/*#**************************************************************************
*#
*#  FUNCTION NAME : extend_operator
*#
*#  PARAMETERS    : x      rtx operation to be tested
*#                  mode   supposed mode of the operation
*#
*#  RETURNS       : 1 or 0 (predicate)
*#
*#  DESCRIPTION   : Check to see if MODE is same as mode for X, 
*#                  and X is SIGN_EXTEND or ZERO_EXTEND.
*#                  Return 1 if so, else 0.
*#                  Intended as a predicate for match_operator.
*#
*#---------------------------------------------------------------------------
*#
*#  HISTORY
*#
*#  DATE     NAME                  CHANGES
*#  ----     ----                  -------
*#  920721   HP                    initial
*#
*#************************************************************************#*/
int
extend_operator(x, mode)
rtx x;
enum machine_mode mode;
{
  enum rtx_code code = GET_CODE(x);

  if (mode == VOIDmode)
    mode = GET_MODE(x);

  return (GET_MODE(x) == mode &&
          (code == SIGN_EXTEND || code == ZERO_EXTEND));
}

/*#**************************************************************************
*#
*#  FUNCTION NAME : plus_or_bound_operator
*#
*#  PARAMETERS    : x      rtx operation to be tested
*#                  mode   supposed mode of the operation
*#
*#  RETURNS       : 1 or 0 (predicate)
*#
*#  DESCRIPTION   : Check to see if MODE is same as mode for X, 
*#                  and X is PLUS or BOUND.
*#                  Return 1 if so, else 0.
*#                  Intended as a predicate for match_operator.
*#---------------------------------------------------------------------------
*#
*#  HISTORY
*#
*#  DATE     NAME                  CHANGES
*#  ----     ----                  -------
*#  930430   HP                    initial
*#
*#************************************************************************#*/
int
plus_or_bound_operator(x, mode)
rtx x;
enum machine_mode mode;
{
  enum rtx_code code = GET_CODE(x);

  if (mode == VOIDmode)
    mode = GET_MODE(x);

  return (GET_MODE(x) == mode
	  && (code == UMIN || code == PLUS));
}

/************************** OTHER SUPPORT ROUTINES **************************/

/*#**************************************************************************
*#
*#  FUNCTION NAME : op_str
*#
*#  PARAMETERS    : x       rtx whose code should be returned as text
*#
*#  RETURNS       : a text string
*#
*#  DESCRIPTION   : Return the text string corresponding to the CODE of
*#                  X.
*#                  Intended for use in the assembly language output
*#                  section of a define_insn.
*#
*#---------------------------------------------------------------------------
*#
*#  HISTORY
*#
*#  DATE     NAME                  CHANGES
*#  ----     ----                  -------
*#  9111??   RW                    Initial
*#
*#************************************************************************#*/
/* This little fix suppresses the 'u' or 's' when '%e' in assembly pattern. */
static char was_bound = 0;
char *
op_str(x)
rtx x;
{
  was_bound = 0;
  switch (GET_CODE(x))
  {
    case PLUS : return "add"; break;
    case MINUS : return "sub"; break;
    case MULT : return "mul"; break;
    case DIV : return "div"; break;
    case AND : return "and"; break;
    case IOR : return "or"; break;
    case XOR : return "xor"; break;
    case NOT : return "not"; break;
    case ASHIFT : return "lsl"; break;
    case LSHIFTRT : return "lsr"; break;
    case ASHIFTRT : return "asr"; break;
    case UMIN: was_bound = 1; return "bound"; break;
    default : return "Unknown operator"; break;
  }
}

/*#**************************************************************************
*#
*#  FUNCTION NAME : function_prologue
*#
*#  PARAMETERS    : file : the file where to print the assembly insn.
*#                  size : the size of allocated stack
*#
*#  RETURNS       : nothing
*#
*#  DESCRIPTION   : print a prologue for a function, inclusive saving
*#                  of registers, varargs handling, allocation of
*#                  stack space etc. 
*#
*#---------------------------------------------------------------------------
*#
*#  HISTORY
*#
*#  DATE     NAME                  CHANGES
*#  ----     ----                  -------
*#  920625   HP                    Init. Realized that this was too
*#                                 much for a macro. 
*#  920814   HP                    Initial adoption to SW standard
*#  940110   HP                    Added stack alignment fix.
*#
*#************************************************************************#*/
void
function_prologue(file, size)
     FILE *file;
     int size;
{
  register int regno;						
  register int c_f_o_a_s = current_function_outgoing_args_size;
  
  int last = -1;
  int framesize = 0;

  fprintf(file,"\ticonst_0\n\tistore 14\n\n");

  return; /* deal with this later */

  if (!TARGET_PROLOGUE_EPILOGUE)
    return;

  if (size < 0) size = 0;

  /* Align the size to even byte count.  Later additions here to this does
     not affect the "alignment".  */
  if (TARGET_STACK_ALIGN)
    size = TARGET_SVINTO ? (size+3)&~3 : (size+1)&~1;

  if (current_function_pretend_args_size) {
    for (regno = FIRST_ARG_REG+MAX_ARGS_IN_REGS-1;
	 regno >= first_vararg_reg; regno--)
    {
      fprintf(file, "\tpush r%d\n",regno);
      framesize += 4;
    }
  }

  /* We have to adjust this afterward. I cannot find the correct
   * place/macro where to straight it up. */
  if (current_function_args_size > 0
      && (!frame_pointer_needed || !regs_ever_live[SRP_REGNUM]))
  {
    fprintf(file,"\tsUBq %d,sp\n",
            frame_pointer_needed == regs_ever_live[SRP_REGNUM]
            ? 8 : 4);

    framesize += (frame_pointer_needed == regs_ever_live[SRP_REGNUM]) ? 8 : 4;
  }

  /* save SRP if not a leaf function */ 
/*  if (regs_ever_live[SRP_REGNUM]) 
  { 
    fprintf(file, "\tPush srp\n"); 
    framesize += 4;
  } */

  /* Set up frame pointer if needed. */ 
  if (frame_pointer_needed)  {
    fprintf(file, "\t; setup frame pointer r%d\n",
	    FRAME_POINTER_REGNUM); 
    framesize += 4;
  }

  for (regno = 0; regno < FIRST_PSEUDO_REGISTER; regno++)	
    if ((regs_ever_live[regno])
	&& !call_used_regs[regno]	
        && !(regno == FRAME_POINTER_REGNUM && frame_pointer_needed) 
        && !(regno == SRP_REGNUM)) { 
      if (regno == last+1)	/* Check if movem may be used.  */
	last++;			/* yes! */
      else {
	/* No, may have to flush movem:ed regs.  */
	if (last != -1) {
	  /* Avoid printing two sub:s for sp */
	  fprintf(file, "\tsub%s %d,sp ; not this one\n",
		  (last+1)*4+size <= 63 ? "q" : (last+1)*4+size <= 255
		  ? "u.b" : (last+1)*4+size <= 65535 ? "u.w" : ".d",
		  (last+1)*4+size);

          framesize += (last+1)*4+size;
	  if (TARGET_PDEBUG)
	    fprintf(file,"; frame %d, #regs %d, bytes %d args %d\n",
		    size,
		    last+1,
		    (last+1)*4,
		    current_function_args_size);

	  fprintf(file, "\tmovem %s,[sp]\n", reg_names[last]);

	  last = -1;
	  size = 0;
	} else  if (size > 0) /* Local vars on stack, no movem; sub! */ {
	  fprintf(file, "\tiload %d\n\tldc %d\n\tistore %d\n\n",
	          STACK_POINTER_REGNUM,size,STACK_POINTER_REGNUM);
          framesize += size;
	  size = 0;
	}
	fprintf(file, "\tPush %s\n", reg_names[regno]);                    
        framesize += 4;
      }
    } 

  /* Check after, if we could movem all push-regs */
  if (last != -1) {
    /* Avoid printing two sub:s for sp */
    fprintf(file, "\tsub%s %d,sp ; 2 not this one\n",
	    (last+1)*4+size <= 63 ? "q" : (last+1)*4+size <= 255
	    ? "u.b" : (last+1)*4+size <= 65535 ? "u.w" : ".d",
	    (last+1)*4+size);
    framesize += (last+1)*4+size;
    if (TARGET_PDEBUG)
      fprintf(file,"; frame %d, #regs %d, bytes %d args %d\n",
	      size,
	      last+1,
	      (last+1)*4,
	      current_function_args_size);
    fprintf(file, "\tmovem %s,[sp]\n", reg_names[last]);

    /* Unfortunately we have to put all local outgoing func args after regs. */
    if (c_f_o_a_s)
    {
      fprintf(file, "\tSub%s %d,sp ; 3 not this one\n",
	      c_f_o_a_s<=63 ? "q"
	      : c_f_o_a_s<=255
	        ? "u.b" : c_f_o_a_s<=65535
	           ? "u.w" : ".d",
	      c_f_o_a_s);
      framesize += c_f_o_a_s;
    }
  } else  if ((size + c_f_o_a_s) > 0) {
    /* local vars on stack, no movem; sub! */
    fprintf(file, "\tiload %d\n\tldc %d\n\tistore %d\n\n",
            STACK_POINTER_REGNUM,size+c_f_o_a_s,STACK_POINTER_REGNUM);
    framesize += size+c_f_o_a_s;
  }
  if (TARGET_PDEBUG)
    fprintf(file,
	    "; parm #%d @ %d; frame %d, FP-SP is %d; leaf: %s%s; fp %s, outg: %d arg %d\n",
          MAX_ARGS_IN_REGS+1, FIRST_PARM_OFFSET(0),
	  get_frame_size(),
	  initial_fp_sp_offset(),
	  leaf_function_p() ? "yes" : "no",
	  regs_ever_live[SRP_REGNUM] ? "no" :"yes",
	  frame_pointer_needed ? "yes" : "no",
	  c_f_o_a_s,current_function_args_size
	  ); 

  if (jvm_max_stackframe && framesize > jvm_max_stackframe)
  {
    warning("Stackframe too big: %d bytes", framesize);
  }
}

/*#**************************************************************************
*#
*#  FUNCTION NAME : saved_regs_mentioned
*#
*#  PARAMETERS    : insn, an rtx
*#
*#  RETURNS       : 1 if there are regs mentioned in the insn that are
*#                  not all in the call_used regs, 0 else.
*#
*#  DESCRIPTION   : Part of the thought if the insn may be put in the epilogue.
*#
*#---------------------------------------------------------------------------
*#
*#  HISTORY
*#
*#  DATE     NAME                  CHANGES
*#  ----     ----                  -------
*#  930428   HP                    Creation
*#
*#************************************************************************#*/

static int
saved_regs_mentioned(x)
     rtx x;
{

  int i;
  char *fmt;
  RTX_CODE code;

  /* Mainly snatched from refers_to_regno_p in rtlanal.c
    We only need to consider slottable insn in the general sence. */

  code = GET_CODE (x);

  switch (code)
    {
    case REG:
      i = REGNO (x);
      
      return !call_used_regs[i];

    case SUBREG:
      /* If this is a SUBREG of a hard reg, we can see exactly which
	 registers are being modified.  Otherwise, handle normally.  */
      i = REGNO (SUBREG_REG (x));
      
      return !call_used_regs[i];
    default: ;
    }

  fmt = GET_RTX_FORMAT (code);
  for (i = GET_RTX_LENGTH (code) - 1; i >= 0; i--)
    {
      if (fmt[i] == 'e')
	{
	  if (saved_regs_mentioned (XEXP (x, i)))
	    return 1;
	}
      else if (fmt[i] == 'E')
	{
	  register int j;
	  for (j = XVECLEN (x, i) - 1; j >=0; j--)
	    if (saved_regs_mentioned (XEXP (x, i)))
	      return 1;
	}
    }

  return 0;
}


/*#**************************************************************************
*#
*#  FUNCTION NAME : eligible_for_epilogue_delay
*#
*#  PARAMETERS    : insn, an rtx
*#
*#  RETURNS       : 1 if the insn may be put in the epilogue, else 0.
*#
*#  DESCRIPTION   : Figure out if the insn may be put in the epilogue.
*#
*#---------------------------------------------------------------------------
*#
*#  HISTORY
*#
*#  DATE     NAME                  CHANGES
*#  ----     ----                  -------
*#  930428   HP                    Creation
*#
*#************************************************************************#*/
int
eligible_for_epilogue_delay(insn)
     rtx insn;
{
  return 0;

  /* First of all, it must be slottable in the general way. 
  if (get_attr_slottable(insn) != SLOTTABLE_YES)
    return 0;*/

  /* There may be references to the stack pointer that are clean to be put
     in the delay slot, but I cant think of a real case. */
  if (reg_mentioned_p(stack_pointer_rtx, PATTERN(insn)))
    return 0;

  /* The frame pointer will also be restored before the "ret". */
  if (frame_pointer_needed
      && reg_mentioned_p(frame_pointer_rtx, PATTERN(insn)))
    return 0;

  /* All regs that will be restored are restored when we come here.
     This means that we cannot have any instructions that mention the
     registers that are restored by the epilogue. */
  if (saved_regs_mentioned(PATTERN(insn)))
    return 0;

  /* It seems to be ok. */
  return 1;
}

/*#**************************************************************************
*#
*#  FUNCTION NAME : delay_slots_for_epilogue
*#
*#  PARAMETERS    : none
*#
*#  RETURNS       : 1 if epilogue contains "ret", else 0.
*#
*#  DESCRIPTION   : Figure out how many delay slots in the epilogue.
*#
*#---------------------------------------------------------------------------
*#
*#  HISTORY
*#
*#  DATE     NAME                  CHANGES
*#  ----     ----                  -------
*#  930428   HP                    Creation
*#
*#************************************************************************#*/
/* Put insn to output here, maybe we can put it in delay slot.
   Used in delay_slots_for_epilogue and function_epilogue. */
static char save_last[80];

int
delay_slots_for_epilogue()
{
  return 0;
  /* Check if return insn. Else no slot to fill. */
  if (regs_ever_live[SRP_REGNUM])
    return 0;

  /* By calling function_epilogue() with same parameters as from gcc
     we can get info about if the epilogue can fill the delay-slot by itself.
      If it is filled from the epilogue, then the corresponding string
     is in save_last.
      This all depends on that the "size" argument to function_epilogue
     always is get_frame_size() */
  function_epilogue(0, get_frame_size());

  if (*save_last)
    return 1;
  return 0;
}

/*#**************************************************************************
*#
*#  FUNCTION NAME : function_epilogue
*#
*#  PARAMETERS    : file : the file where to print the assembly insn.
*#                  size : the size of allocated stack
*#
*#  RETURNS       : nothing
*#
*#  DESCRIPTION   : print a epilogue for a function, inclusive restoring
*#                  of registers, varargs handling, deallocation of
*#                  stack space etc.   Also checks if there is a 'ret'
*#                  instruction that has a delay slot to be filled.
*#
*#---------------------------------------------------------------------------
*#
*#  HISTORY
*#
*#  DATE     NAME                  CHANGES
*#  ----     ----                  -------
*#  920625   HP                    Init. Realized that this was too
*#                                 much for a macro. 
*#  920814   HP                    Initial adoption to SW standard
*#  950622   HP                    Bugfix when using frame-pointer
*#
*#************************************************************************#*/
void
function_epilogue(file, size)
     FILE *file;
     int size;
{
  register int regno;						
  int last = -1;
  rtx insn = get_last_insn();
  int argspace = current_function_outgoing_args_size;
  int pretend =  current_function_pretend_args_size;

  if (my_current_function_name)                      \
      free(my_current_function_name);
  my_current_function_name=0;
  if (TREE_CODE(TREE_TYPE(DECL_RESULT(current_function_decl)))==VOID_TYPE)
    fprintf(file,"\treturn\n.end method\n\n");
  else
    fprintf(file,"\tiload 10\n\tireturn\n.end method\n\n");
  return;

  save_last[0] = 0;

  /* free() my_current_function_name if this is a *real* call of
     function_epilogue() */
  if (file && my_current_function_name)
  {
    free(my_current_function_name);
    my_current_function_name = NULL;
  }

  if (file && !TARGET_PROLOGUE_EPILOGUE)
    return;

  if (TARGET_PDEBUG && file)
    fprintf(file,";;\n");

  /* Align byte count of stack frame.  No additions must be of odd
     count! */
  if (TARGET_STACK_ALIGN)
    size = TARGET_SVINTO ? (size+3)&~3 : (size+1)&~1;

  /* If the last insn was a BARRIER, we don't have to write any code.  */
  if (GET_CODE (insn) == NOTE)
    insn = prev_nonnote_insn (insn);
  if (insn
      && (GET_CODE (insn) == BARRIER
	  /* Watch out! We must be sure that the insn really is
	     a "return" and not a conditional branch.  Try to match
	     the return exactly, and if it doesnt match, assume
	     it is a conditional branch (and output an epilogue) */
	  || (GET_CODE(insn) == JUMP_INSN
	      && GET_CODE(PATTERN(insn)) == RETURN)))
    {
      if (TARGET_PDEBUG && file)
	fprintf (file, ";;;;;\n");
      return;
    }

  /* Check how many regs we can movem */
  for (regno = 0; regno < FIRST_PSEUDO_REGISTER; regno++)	
    if ((regs_ever_live[regno])
	&& !call_used_regs[regno]	
        && !(regno == FRAME_POINTER_REGNUM && frame_pointer_needed) 
        && !(regno == SRP_REGNUM)) {
      if (regno == last+1)	/* Check if movem may be used.  */
	last++;			/* yes! */
      else break;
    }

  for (regno = FIRST_PSEUDO_REGISTER-1; regno > last; regno--)	
    if ((regs_ever_live[regno])
	&& !call_used_regs[regno]	
        && !(regno == FRAME_POINTER_REGNUM && frame_pointer_needed) 
        && !(regno == SRP_REGNUM)) {
      if (argspace) {
	/* These are located before saved registers.  */
	if (file)
	  fprintf(file, "\tAdd%s %d,sp\n",
		  argspace<=63 ? "q"
		  : argspace<=255
	          ? "u.b" : argspace<=65535
		  ? "u.w" : ".d",
		  argspace); 
	/* Make this happen only once. Simplifies code below, too. */
	argspace = 0;
      }
      if (*save_last && file)
	fprintf(file,save_last);
      sprintf(save_last, "\tPop %s\n", reg_names[regno]); 
    }

  if (last != -1) {
    if (argspace) {
      /* These are located before saved registers.  */
      if (file)
	fprintf(file, "\tAdd%s %d,sp\n",
		argspace<=63 ? "q"
		: argspace<=255
	        ? "u.b" : argspace<=65535
		? "u.w" : ".d",
		argspace); 
      /* Make this happen only once. Simplifies code below, too. */
      argspace = 0;
    }
    if (*save_last && file)
      fprintf(file, save_last);
    sprintf(save_last,"\tmovem [sp+],%s\n", reg_names[last]);
  }

  /* Restore frame pointer if necessary.  */ 
  if (frame_pointer_needed) {
    /* Bug correction here; forgot to skip local variable space (move fp->sp) */
    if (*save_last && file)
      fprintf(file, save_last);
/*    if (file)
      fprintf(file,"\tmove.d r%d,sp\n",FRAME_POINTER_REGNUM);*/
    sprintf(save_last, "\t; restore frame pointer r%d\n",FRAME_POINTER_REGNUM);
  }
  else /* Must explicitly dealloc local variables.  */ {
    size += argspace; /* Include accumulated args if no regs saved.  */
    if (size) {
      if (*save_last && file)
	fprintf(file, save_last);
      sprintf(save_last, "\tadd%s %d,sp\n",
	      size<=63 ? "q"
	      : size<=255 ? "u.b" : size<=65535 ? "u.w" : ".d",
	      size);
    }
    if (size > 63) {
      if (file)
	fprintf(file, save_last);
      *save_last = 0;
    }
  }  
  
  /* We have to adjust this afterward. I cannot find the correct
   * place/macro where to straighten it up. */
  if (current_function_args_size > 0
      && (!frame_pointer_needed || !regs_ever_live[SRP_REGNUM]))
    pretend += (frame_pointer_needed == regs_ever_live[SRP_REGNUM]) ? 8 : 4;

  /* If this function has no pushed register params (varargs),
     and if it is not a leaf function, then just jump-return
   */
  if (regs_ever_live[SRP_REGNUM] /* srp lives => not a leaf */ 
      && pretend == 0) {
    if (*save_last && file)
      fprintf(file, save_last);
    if (file)
      fprintf(file, "\tJump [sp+]\n");
    *save_last = 0;
    if (file && current_function_epilogue_delay_list)
      fatal("Unused delay list");
    return;
  }

  /* If we pushed some register params, then remove them. */
  if (pretend) {

    /* Pop srp first, if it was pushed. */
    if (regs_ever_live[SRP_REGNUM] && 0) {  // srp.. blah
      if (*save_last && file)
	fprintf(file, save_last);
      *save_last = 0;
      if (file)
	fprintf(file, "\tpop srp\n");
    }

    if (*save_last && file)
      fprintf(file, save_last);
    sprintf(save_last, "\tadd%s %d,sp\n",
	    pretend <=63 ? "q"
	    : pretend <=255
	    ? "u.b" : pretend <=65535
	    ? "u.w" : ".d",
	    pretend);
  }

  /* If gcc did the job for us, then dont spoil it. */
  if (file && current_function_epilogue_delay_list
      && *save_last) {
    fprintf(file, save_last);
    *save_last = 0;
  }
    
  if (file)
    fprintf(file, "\tRet\n");

  /* Output an insn in the delayed branch. */
  /* Did the Gcc core do the job for us? */
  if (file && current_function_epilogue_delay_list)
    final_scan_insn(XEXP(current_function_epilogue_delay_list, 0),
		    file, 1, -2, 1);
  else if (file) {
    if (*save_last)
      fprintf(file, save_last);
    else
      fprintf(file,"\tnOp\n");
  }
}

/* Use to force "+0" if [reg+0] */
static int print_plus0 = 0;

/*#**************************************************************************
*#
*#  FUNCTION NAME : print_operand
*#
*#  PARAMETERS    : file : the file where to print the operand.
*#                  x    : the operand as an rtx
*#                  code : a character that shows the format to print
*#                         the operand in
*#
*#  RETURNS       : nothing
*#
*#  DESCRIPTION   : print an rtx using the format showed by code, or
*#                  do other hairy things with the operand indicated
*#                  by the code. 
*#                  Used to output operands to the assembly file. The
*#                  code is derived from the format string in the md-file.
*#
*#---------------------------------------------------------------------------
*#
*#  HISTORY
*#
*#  DATE     NAME                  CHANGES
*#  ----     ----                  -------
*#  920625   HP                    Init. Realized that this was too
*#                                 much for a macro. 
*#  920814   HP                    Initial adoption to SW standard
*#  930402   HP                    's' now writes 'b' 'w' for <= 255 65535
*#  930429   HP                    New: 'z' prints 'b' for -128 <= x <= 255
*#                                 or 'w' for -32768 <= x <= 65535 or abort.
*#
*#************************************************************************#*/
void
print_operand(file, x, code)
     FILE *file;
     rtx x;
     int code;
{
  rtx foo = x; 
  rtx op;
  static int caught_int = 0;
  static char *mults[] = { "BAD:0", ".b", ".w", "BAD:3", ".d" };

  PO_PRINTF("PRINT_OPERAND:\n"); 
  PO_RTX(foo); 
  

  /* Add entries for new code here. If finished, just return, else,
     to print the operand (in foo, not x), break.  You may adjust the
     value in foo to whatever you want to be printed. */

  switch (code) {

  case 'b':
    /*
     * Print the unsigned supplied integer as if it was signed and < 0, i.e 
     * print 255 or 65535 as -1, 254, 65534 as -2, etc.
     */
    if (GET_CODE(x) != CONST_INT || !CONST_OK_FOR_LETTER_P(INTVAL(x),'O')) {
      debug_rtx(x);
      fatal("Internal: 'b' not with allowed integer");
    }
    fprintf(file,"%d",INTVAL(x)|(INTVAL(x) <= 255 ? ~255 : ~65535));
    return;

  case 'R':
    /* Check if we could substitute the operand for something cheaper.
     * Sometimes gcc overlooks some possibilities to cse address-operands.
     */
    foo = same_ref_as_saved(0,x);

    /* If we succeded in replacing, indicate by adding "+0" for debugging. */
    if (foo != x)
      print_plus0 = 1;
    break;

  case 'x':
    /* Print assembler code for operator.  */
    fprintf(file,"%s",op_str(foo));
    return;
    
  case 'p':
    /* Adjust a power of two to its log2 */
    if (GET_CODE(x) != CONST_INT || exact_log2(INTVAL(x)) < 0 ) {
      debug_rtx(x);
      fatal("Internal err: 'p' when not const_int and power of 2 on operand above");
    }
    fprintf(file,"%d",exact_log2(INTVAL(x)));
    return;
    
    /* NOT USED. */
  case 'g':
    /* Adjust a power of 2 to log2(x)-1 */
    if (GET_CODE(x) != CONST_INT || exact_log2(INTVAL(x)) < 0 ) {
      debug_rtx(x);
      fatal("Internal err: 'g' when not const_int and power of 2 on operand above");
    }
    fprintf(file,"%d",exact_log2(INTVAL(x))-1);
    return;
    
  case 's':
    /* Just print the size of the operand, not the operand itself.  */

    /* Special cases: print 'b' or 'w' if <= 255 or <= 65535 respectively. */
    if (GET_MODE(x) == VOIDmode && GET_CODE(x) == CONST_INT) {
      if (INTVAL(x) >= 0) {
	if (INTVAL(x) <= 255)
	  putc('b',file);
	else if (INTVAL(x) <= 65535)
	  putc('w',file);
	else
	  putc('d',file);
      } else
	putc('d',file);
      return;
    }
    /* Else print size of operand. */
    putc((GET_MODE(x) == SImode || GET_MODE(x) == SFmode)
	 ? 'd' : GET_MODE(x) == HImode ? 'w'
	 : GET_MODE(x) == QImode ? 'b' : 'X', /* X to get error from jvm. */
	 file);
    return;

  case 'z':
    /* Const_int: print b for -127 <= x <= 255, w for -32768 <= x <=
       65535, else abort */
    if (GET_CODE(x) != CONST_INT
	|| INTVAL(x) < -32768 || INTVAL(x) > 65535)
      fatal("Internal err: 'z' used with non const_int, or out of range");
    putc(INTVAL(x) >= -128 && INTVAL(x) <= 255 ? 'b' : 'w', file);
    return;

  case '#':
    /* Output a 'nop' if there's nothing for the delay slot.
       (This method snatched from the sparc files.)  */
/*    if (dbr_sequence_length () == 0)
      fputs ("\n\tnop", file);*/
    return;
    
  case 'H':
    /* Print high (most significant) part of something. */
    switch(GET_CODE(foo)) {
      
    case CONST_INT:
      /* Sign-extension from a normal int to a long long. */
      fprintf(file, INTVAL(foo) < 0 ? "-1" : "0");
      return;
      
    case CONST_DOUBLE:
      /* A little hairier, get high part of long long. */
      if (GET_MODE(foo) == VOIDmode) /* long long */ {
	fprintf(file,"0x%x",CONST_DOUBLE_HIGH(x));
	return;
      } else {
	debug_rtx(x);
	fatal ("Above used with 'H'; not supported.");
      }
      
    case REG:
      /* Print reg+1. It has no meaning to print high-parts of registers
         whose high-part is stack-pointer or higher. */
      if (REGNO(foo) > STACK_POINTER_REGNUM-2)
	fatal("Internal: Bad register: %d",REGNO(foo));
      fprintf(file,"%s",reg_names[REGNO(foo)+1]);
      return;
      
    case MEM:
      /* Adjust memory address to high part.  Must be asserted to be 
         offsettable, else abort. */
      {
	rtx adj_mem = foo;
	size_of_addr_mode = GET_MODE_BITSIZE(GET_MODE(foo))/BITS_PER_UNIT;
	
	/* Adjust so we can use two SImode in DImode */
	adj_mem = adj_offsettable_operand(adj_mem,size_of_addr_mode/2);
	
	output_address(XEXP(adj_mem, 0)); /* Uses size_of_addr_mode */
	size_of_addr_mode = 0;
	return;
      }
      
    default:
      debug_rtx(x);
      fatal("Above used with 'H', not supported");
    }
	 
  case 'L':
    fprintf(file,"%i",GET_CODE(foo));
    /*foo = XEXP(foo, 0);  strip the MEM expression */ 
    return;

  case 'e':
    /* Print 's' if foo is SIGN_EXTEND or 'u' if ZERO_EXTEND unless
       static char was_bound == 1. */
    if (GET_CODE(foo) != SIGN_EXTEND && GET_CODE(foo) != ZERO_EXTEND
	&& GET_CODE(foo) != CONST_INT) {
      debug_rtx(x);
      fatal("Internal: 'e' not used with zero/sign-extend operator");
    }
    if (was_bound) {
      was_bound = 0;
      return;
    }
    putc(GET_CODE(foo) == SIGN_EXTEND
	 || (GET_CODE(foo) == CONST_INT && INTVAL(foo) < 0)
	 ? 's' : 'u',file);
    return;

  case 'm':
    /* Print the size letter of element in vector.  */
    if (GET_CODE(foo) != SIGN_EXTEND && GET_CODE(foo) != ZERO_EXTEND) {
      debug_rtx(x);
      fatal("Internal: 'm' not used with zero/sign-extend operator");
    }
    print_operand(file,XEXP(foo,0),'s');
    return;

  case 'M':
    /* Print least significant part of foo. */
    if (GET_CODE(foo) == CONST_DOUBLE) {
      fprintf(file,"0x%x",CONST_DOUBLE_LOW(x));
      return;
    } /* Else take care of it as normal value.  */
    break;

  case 'C':
    /* Collect the const_int part of foo.  Dont print. */
    caught_int = 0;
    if (GET_CODE(foo) == CONST_INT) {
      caught_int = INTVAL(foo);
      return;
    }

    if (GET_CODE(foo) == SYMBOL_REF || GET_CODE(foo) == LABEL_REF)
      return;

    if (GET_CODE(foo) == CONST)
      caught_int = INTVAL(XEXP(XEXP(foo,0),1));
    else {
      debug_rtx(foo);
      fatal("Internal: 'C' not used with non-const above");
    }
    return;

  case 'P':
    /* Print the sum of the caught int and the int-part of foo. Signed. */
    {
      int tem = caught_int;

      /* Easy way to find the int-part. */
      print_operand(file,foo,'C'); 
      fprintf(file,"%s%d",(tem+caught_int) < 0 ? "" : "+", (tem+caught_int));
      return;
    }
    
  case 'S':
    {
      /* If foo is a const_int, then be sure that its sign-letter
         (additive operator) is printed.  Else it is a register or a
	 mult between a register and 2 or 4.  Print as r.S where S is
	 d, w or b.
	 930430 May also be (mem:SI (reg_or_autoincr x)) and
	       (sign_extend:SI (mem:QI|HI (reg_or_autoincr x)))
	 */
      int mult=1;
      
      /* Use this to print '+' for positive constants. */
      if (CONSTANT_P(foo)) {
	if (GET_CODE(foo) != CONST_INT || INTVAL(foo) >= 0)
	  putc('+',file);
	break;
      }
      
      /* Always print '+' (when not negative integer).
         But not when we will use print_index. */
      if (GET_CODE(foo) != MEM && GET_CODE(foo) != SIGN_EXTEND)
	putc('+',file);
      
      if (GET_CODE(foo) != REG && GET_CODE(foo) != MULT
	  && GET_CODE(foo) != MEM && GET_CODE(foo) != SIGN_EXTEND) {
	debug_rtx(x);
	fatal ("bad output-format S for above operand");
      }
      
      if (GET_CODE(foo) == MEM && BASE_OR_AUTOINCR_P(XEXP(foo,0))) {
	PRINT_INDEX(foo,file);
	return;
      }

      if (GET_CODE(foo) == SIGN_EXTEND
	  && GET_CODE(XEXP(foo,0)) == MEM
	  && BASE_OR_AUTOINCR_P(XEXP(XEXP(foo,0),0))) {
	PRINT_INDEX(foo,file);
	return;
      }

      if (GET_CODE(foo) == MULT) {
	if (GET_CODE(XEXP(foo,0)) == REG) {
	  if (GET_CODE(XEXP(foo,1)) != CONST_INT) {
	    debug_rtx(x);
	    fatal ("bad output-format S for above operand");
	  }
	  mult = INTVAL(XEXP(foo,1));
	  foo = XEXP(foo,0);
	} else if (GET_CODE(XEXP(foo,1)) == REG) {
	  if (GET_CODE(XEXP(foo,0)) != CONST_INT) {
	    debug_rtx(x);
	    fatal ("bad output-format S for above operand");
	  }
	  mult = INTVAL(XEXP(foo,0));
	  foo = XEXP(foo,1);
	} else {
	  debug_rtx(x);
	  fatal ("bad output-format S for above operand");
	}
      } else if (GET_CODE(foo) != REG) {
	debug_rtx(x);
	fatal ("bad output-format S for above operand");
      }
      
      if (REGNO(foo) > 15)
	fatal("Internal: Bad register: %d",REGNO(foo));
      fprintf (file, "%s%s", reg_names[REGNO (foo)], mults[mult]);
      return;
    }

  case 'T':
    /* Print size letter for foo, which must be a const_int. */
    if (GET_CODE(foo) != CONST_INT || INTVAL(foo) > 4) {
      debug_rtx(x);
      fatal("Above used with T, cannot resolve",code);
    }

    fprintf(file,"%s",mults[INTVAL(foo)]);
    return;

  case 'J':
     fprintf(file, "Prog"); /*,my_class_name);*/
     return;	

  case 'K':
    if (GET_CODE(foo) == SYMBOL_REF) {
      fprintf(file, "symref%s",my_class_name);
      assemble_name(file, XEXP(x,0)); 
      fprintf(file,"end");
    } else 
    /*if (GET_CODE(foo) == CONST_INT)*/ {
      if (INTVAL(foo)>-129 && INTVAL(foo)<128)
        fprintf(file, "bipush %i",INTVAL(foo));
      else
      if (INTVAL(foo)>-32769 && INTVAL(foo)<32768)
        fprintf(file, "sipush %i",INTVAL(foo));
      else
	fprintf(file,"ldc %i",INTVAL(foo));
    } 
     return;	

  case 0:
    /* No code, print as usual. */
    break;
    
  default:
    debug_rtx(x);
    fatal("Above used with bad format: '%c'",code);
  }
  
  /* Normal print routine. */
  switch(GET_CODE(foo)) {

  case REG:
      if (REGNO(foo) > 15)
	fatal("Internal: Bad register: %d",REGNO(foo));
    fprintf (file, "%s", reg_names[REGNO (foo)]);
    return;

  case MEM:
/*    op = XEXP(foo,0);
    switch(GET_CODE(op)) {
      case CONST_INT: fprintf(file,"ldc %i",INTVAL(op)); break;
      case PLUS: 
  		 if (GET_CODE(XEXP(op,0))==REG) 
                   fprintf(file,"iload %s\n\t",reg_names[REGNO(XEXP(op,0))]);
                 else if (GET_CODE(XEXP(op,0))==CONST_INT)
                   fprintf(file,"ldc %i\n\t",INTVAL(XEXP(op,0)));
                 else 
                   fprintf(file,"unknownmem\n\t");
  		 if (GET_CODE(XEXP(op,1))==REG) 
                   fprintf(file,"iload %s\n\t",reg_names[REGNO(XEXP(op,0))]);
                 else if (GET_CODE(XEXP(op,0))==CONST_INT)
                   fprintf(file,"ldc %i\n\t",INTVAL(XEXP(op,0)));
                 else 
                   fprintf(file,"unknownmem\n\t");
                 fprintf(file,"iadd");
		 break;                 
      case REG: fprintf(file,"iload %s",reg_names[REGNO(op)]); break;	
    }
    output_address(XEXP(foo, 0)); */
    print_operand_address(file,XEXP(foo,0));
    return;

  case CONST_DOUBLE:
    /* Only single is supported for the moment.  */
    if (GET_MODE(foo) == VOIDmode) /* long long */ {
      output_addr_const(file, foo); 
    } else {
      union { float f; int i; } u1;
      REAL_VALUE_FROM_CONST_DOUBLE (u1.f,foo);
#ifndef JVM_FLOAT_NOT_BROKEN_ANY_MORE
      fprintf (file, "0x%x", u1.i);    
#else /* JVM_FLOAT_NOT_BROKEN_ANY_MORE */
      fprintf(file,"0s%.10g",u1.f);
#endif /* JVM_FLOAT_NOT_BROKEN_ANY_MORE */
    }
    return;

  case CONST:
    output_addr_const(file, foo); 
    return;
    
  case MULT: case ASHIFT:
    {
      int i = GET_CODE(XEXP(foo,1)) == CONST_INT
	? INTVAL(XEXP(foo,1)) : INTVAL(XEXP(foo,0));
      rtx reg = GET_CODE(XEXP(foo,1)) == CONST_INT
	? XEXP(foo,0) : XEXP(foo,1);
      
      if (GET_CODE(reg) != REG
	  || (GET_CODE(XEXP(foo,0)) != CONST_INT
	      && GET_CODE(XEXP(foo,1)) != CONST_INT)) {
	debug_rtx(x);
	fatal("Can't print operand");
      }

      PRINT_BASE(reg,file);
      fprintf(file,".%c",
	      /* Check if byte (then this should be a normal add!) */
	      i == 0 || (i == 1 && GET_CODE(foo) == MULT) ? 'b'
	      /* Check for 32bit, mult */
	      : i == 4 ? 'd' /* Assume mult */
	      /* Check for 16bit */
	      : (i == 2 && GET_CODE(foo) == MULT) || i == 1 ? 'w'
	      : 'd');
      return;
    }

  default:
    /* No need to include all the strange things.
       Let output_addr_const do it for us.  */
    if (CONSTANT_P(foo)) {
      output_addr_const(file,foo);
      return;
    }
    debug_rtx(x);
    fatal("Cannot decode operand above");
  }
}

/*#**************************************************************************
*#
*#  FUNCTION NAME : print_operand_address
*#
*#  PARAMETERS    : file : the file where to print the operand address.
*#                  x    : the operand as an rtx
*#
*#  RETURNS       : nothing
*#
*#  DESCRIPTION   : print an rtx as an address. 
*#                  Used to output operand addresses to the assembly file.
*#
*#---------------------------------------------------------------------------
*#
*#  HISTORY
*#
*#  DATE     NAME                  CHANGES
*#  ----     ----                  -------
*#  920625   HP                    Init. Realized that this was too
*#                                 much for a macro. 
*#  920814   HP                    Initial adoption to SW standard
*#
*#************************************************************************#*/
void
print_operand_address(file, x)
     FILE *file;
     rtx x;
{
  rtx foo1, foo2; 

  switch(GET_CODE(x)) {
    case CONST:
    case CONST_INT:  fprintf(file,"ldc %i",INTVAL(x)); break;
    case REG: fprintf(file,"iload %s",reg_names[REGNO(x)]); break;
    case MEM: fprintf(file,"aload_0\n\tgetfield %s/memory [I\n\t",my_class_name);
	      print_operand_address(file,XEXP(x,0)); 
	      fprintf(file,"\n\tdup2\n\tiaload\n\tbipush 8\n\tishl\n\tdup_x2\n\tpop\n\ticonst_1\n\tiadd\n\tdup2\n\tiaload\n\tbipush 16\n\tishl\n\tdup_x2\n\tpop\n\ticonst_1\n\tiadd\n\tdup2\n\tiaload\n\tbipush 8\n\tishl\n\tdup_x2\n\tpop\n\ticonst_1\n\tiadd\n\tiaload\n\tior\n\tior\n\tior");
	      break;
    case SYMBOL_REF: fprintf(file,"symref%s",my_class_name);
		     assemble_name(file, XEXP(x,0)); 
		     fprintf(file,"end");
		     break;
    case PLUS: print_operand_address(file,XEXP(x,0));
	       fprintf(file,"\n\t");
	       print_operand_address(file,XEXP(x,1));
	       fprintf(file,"\n\tiadd");
	       break;	 	 	
    case MINUS: 
	       print_operand_address(file,XEXP(x,0));
	       fprintf(file,"\n\t");
	       print_operand_address(file,XEXP(x,1));
	       fprintf(file,"\n\tisub");
	       break;	 
    case MULT:
	       print_operand_address(file,XEXP(x,0));
	       fprintf(file,"\n\t");
	       print_operand_address(file,XEXP(x,1));
	       fprintf(file,"\n\timul");
	       break;	 	
    default: fprintf(file,"unknownmem %i",GET_CODE(x));
  }

/*  PO_PRINTF("PRINT_OPERAND_ADDRESS:\n"); 
  PO_RTX(x); 

  putc('[', file); 

  if (CONSTANT_ADDRESS_P(x)) 
    output_addr_const(file, x); 
  else if (BASE_OR_AUTOINCR_P(x)) 
    { PRINT_BASE(x, file); } 
  else if (GET_CODE(x) == PLUS) 
    { 
      foo1 = XEXP(x, 0); 
      foo2 = XEXP(x, 1); 
      if (BASE_P(foo1)) 
	{ 
	  PRINT_BASE(foo1, file); 
	  PRINT_INDEX(foo2, file); 
	} 
      else if (BASE_P(foo2)) 
	{ 
	  PRINT_BASE(foo2, file); 
	  PRINT_INDEX(foo1, file); 
	} 
      else 
	PO_PRINTF("Bad index mode!\n"); 
    } 
  else if (GET_CODE(x) == MEM) 
    { 
      putc('[', file); 
      PRINT_BASE(XEXP(x, 0), file); 
      putc(']', file); 
    } 
  else 
    { 
      PO_PRINTF("?Can't print operand address\n"); 
    } 
  if (print_plus0) {
    fputs("+0",file);
    print_plus0 = 0;
  }
  putc(']', file); */
}


/*#**************************************************************************
*#
*#  FUNCTION NAME : initial_fp_sp_offset
*#
*#  PARAMETERS    : none. All information are in global variables
*#
*#  RETURNS       : the difference between the address after a
*#                  possibly saved return address; the location of a
*#                  (imaginary) frame pointer and the stack pointer
*#
*#  DESCRIPTION   : looks through register descriptors and frame size
*#                  to find it out. 
*#                  Used when to eliminate the frame pointer.
*#
*#---------------------------------------------------------------------------
*#
*#  HISTORY
*#
*#  DATE     NAME                  CHANGES
*#  ----     ----                  -------
*#  920625   HP                    Init. Realized that this was too
*#                                 much for a macro. 
*#  920814   HP                    Initial adoption to SW standard
*#
*#************************************************************************#*/
int
initial_fp_sp_offset()
{
  int regno;

  /* Initial offset is 0 if we dont have a frame pointer.
      Note that this applies to the stack frame only.
     The is no way to say that previous parameter offset
     must be decreased by four. */
  int offs = 0;
  
  /* And 4 for each register pushed.  */
  for (regno = 0; regno < FIRST_PSEUDO_REGISTER; regno++)	
    if (regs_ever_live[regno]
	&& !call_used_regs[regno]	
        && !(regno == FRAME_POINTER_REGNUM && frame_pointer_needed) 
        && !(regno == SRP_REGNUM))
      offs += 4;

  /* And then, last, we add the locals allocated.  */
  offs += get_frame_size();

  /* And more; the accumulated args size */
  offs += current_function_outgoing_args_size;

  /* Then round it off, in case we use aligned stack. */
  if (TARGET_STACK_ALIGN)
    offs = TARGET_SVINTO ? (offs+3)&~3 : (offs+1)&~1;

  return offs;
}

/*#**************************************************************************
*#
*#  FUNCTION NAME : notice_update_cc
*#
*#  PARAMETERS    : exp  : the pattern of an insn
*#                  insn : the body of the insn.
*#
*#  RETURNS       : nothing. The global variable cc_status is changes
*#                  to reflect possible usage of the condition codes
*#                  from this insn. 
*#
*#  DESCRIPTION   : looks into the pattern to see how this insn
*#                  affects condition codes. Used when to eliminate
*#                  test insns before a condition code user, such as a
*#                  Scc insn or a conditional branch. 
*#                   This includes checking if the entities that cc
*#                  was updated by are changed by the operation. In
*#                  speak, this means that if cc was updated by a
*#                  "test [r5+r7.W]" and the insn we are checking is
*#                  "move.d r4,[r5+r7.W]" (that do not normally
*#                  change cc) then cc_status should be initialized,
*#                  since it no longer reflects the value at [r5+r7.w].
*#                  See "Using and porting gcc 2.0", feb 92 for details.     
*#
*#---------------------------------------------------------------------------
*#
*#  HISTORY
*#
*#  DATE     NAME                  CHANGES
*#  ----     ----                  -------
*#  920625   HP                    Init. Realized that this was too
*#                                 much for a macro. 
*#  920814   HP                    Initial adoption to SW standard
*#  960103   HP                    Did not recognize a set to a
*#                                 a strict_low_part of a mem.  Now does.
*#                                 Did not recognize a set from a
*#                                 label_ref.  Now does.
*#  960106   HP                    Added a check of overlap-mentioned
*#                                 for the Scc instructions.
*#
*#************************************************************************#*/
void
notice_update_cc(exp, insn)
     rtx exp;
     rtx insn;
{
  /* If something goes wrong, we can eliminate this routine
     (which may be a suspect) by doing -mcc-init */
  if (TARGET_CCINIT) {
    CC_STATUS_INIT;
    return;
  }

  if (GET_CODE(exp) == SET) {

    /* Jumps/branches do not change cc.  */
    if (SET_DEST(exp) == pc_rtx || SET_SRC(exp) == pc_rtx) {
      return;
    }
    
    /* CC0 changes should be recorded, so we wont have to output them twice. */
    if (SET_DEST(exp) == cc0_rtx) {
      cc_status.value1 = SET_SRC(exp);
      cc_status.value2 = 0;

      /* Handle flags for the special btstq on one bit here. */
      if (GET_CODE(SET_SRC(exp)) == ZERO_EXTRACT
	  && XEXP(SET_SRC(exp),1) == const1_rtx) {
	if (GET_CODE(XEXP(SET_SRC(exp),0)) == CONST_INT)
	  cc_status.flags = CC_INVERTED; /* Use cmpq */
	else
	  cc_status.flags = CC_Z_IN_NOT_N; /* one-bit btstq */
      } else
	cc_status.flags = 0;	/* Init any flags, dont save old.  */

      if (GET_CODE(SET_SRC(exp)) == COMPARE) {
	if (!REG_P(XEXP(SET_SRC(exp),0))
	    && XEXP(SET_SRC(exp),1) != const0_rtx)
	  /* For some reason gcc wont canonicalize compare operations,
	     reversing the sign by itself if operands are in wrong order.
	     */
	  cc_status.flags = CC_REVERSED; /* NOT inverted; eq is still eq. */
	
	/* This is overlooked by gcc. (Provably?) */
	cc_status.value2 = gen_rtx(MINUS, GET_MODE(SET_SRC(exp)),
				   XEXP(SET_SRC(exp),0),
				   XEXP(SET_SRC(exp),1));
      }
      return;
    }

    /* Function calls change cc.  */
    if (GET_CODE (SET_SRC (exp)) == CALL) {
      CC_STATUS_INIT; 
      return;
    }
    
    
    /* If not to cc0, then no assign in non-natural mode gives ok cc0.  */
    if (GET_MODE_SIZE(GET_MODE(SET_DEST(exp))) > UNITS_PER_WORD
	|| GET_MODE_CLASS(GET_MODE(SET_DEST(exp))) == MODE_FLOAT) {
      /* Except adds and subs in DImode. */
      if (GET_MODE(SET_DEST(exp)) == DImode
	  && (GET_CODE(SET_SRC(exp)) == PLUS
	      || GET_CODE(SET_SRC(exp)) == MINUS)) {
	cc_status.flags = 0;
	cc_status.value1 = SET_DEST(exp);
	cc_status.value2 = SET_SRC(exp);
	if (my_reg_overlap_mentioned_p(cc_status.value1,cc_status.value2))
	  cc_status.value2 = 0;
	return;
      }
      CC_STATUS_INIT;
      return;
    }

    if (REG_P (SET_DEST (exp))
	|| (GET_CODE(SET_DEST(exp)) == STRICT_LOW_PART
	    && REG_P(XEXP(SET_DEST(exp),0))))
      { /* A register is set; normally cc is set to reflect no test instr
	   needed. Catch the exceptions. */
	
	/* Check if value 0. Then no change in cc. (clear instruction)
	   Catch if reg is mentioned in last cc-val.  */
	if (SET_SRC(exp) == CONST0_RTX(GET_MODE(SET_DEST(exp)))) {
	  if (cc_status.value1
	      && my_reg_overlap_mentioned_p(SET_DEST(exp),
					 cc_status.value1))
	    cc_status.value1 = 0;
	  
	  if (cc_status.value2
	      && my_reg_overlap_mentioned_p(SET_DEST(exp),
					 cc_status.value2))
	    cc_status.value2 = 0;
	  return;
	}
	
	/* The arithmetic codes that clobber cc in unpredictable ways.
	   If you find that, then CC_STATUS_INIT & return, else if the cc
	   is ok to eliminate a test insn against source or dest, break. */
	switch (GET_CODE(SET_SRC(exp))) {
	case IF_THEN_ELSE:
	  /* One of those weird mstep (or dstep) insns, from mul expands.
	     */
	  cc_status.value1 = SET_DEST(exp);
	  cc_status.value2 = 0;
	  return;

	case IOR:
	case AND: /* if quick and <= 0 then bad for all but SImode.  */
	  if (GET_MODE(SET_DEST(exp)) != SImode
/*	      && get_attr_slottable(insn) == SLOTTABLE_YES*/
	      && ((GET_CODE(XEXP(SET_SRC(exp),0)) == CONST_INT
		   && (XINT(SET_SRC(exp),0) <= 0
		       || (XINT(SET_SRC(exp),0)
			   >= GET_MODE_MASK(GET_MODE(SET_DEST(exp))-31))))
		  /* Is this needed? Should not, if trust insn canonicalization. */
		  || ((GET_CODE(XEXP(SET_SRC(exp),1)) == CONST_INT)
		      && ((XINT((SET_SRC(exp)),1) <= 0)
			  || (XINT(SET_SRC(exp),0)
			      >= (GET_MODE_MASK((GET_MODE((SET_DEST(exp)))-31)))))))) {
	    CC_STATUS_INIT;
	    return;
	  }
	  break;
	  
	case PLUS:
	  if (GET_CODE(XEXP(SET_SRC(exp),0)) == MULT) /* addi rx.S, ry */
	    {
	      CC_STATUS_INIT;	/* This may change; the specs are unclear.  */
	      return;
	    }
	  /* Fall into... */
	case MINUS:
	  /* If we "addq/subq" then cc is bad for byte and 16bit.
	     This test includes quickened add/sub */
	  if (/*get_attr_slottable(insn) == SLOTTABLE_YES
	      &&*/ ((GET_CODE(XEXP(SET_SRC(exp),0)) == CONST_INT
		  || (GET_CODE(XEXP(SET_SRC(exp),1)) == CONST_INT))
		  && GET_MODE(SET_DEST(exp)) != SImode)) {
	    CC_STATUS_INIT;
	    return;
	  }
	  /* Check for adds/addu/subs/subu to HImode. That gives bad cc. */
	  if (GET_MODE(SET_DEST(exp)) == HImode
	      && (GET_CODE(XEXP(SET_SRC(exp),0)) == ZERO_EXTEND
		  || GET_CODE(XEXP(SET_SRC(exp),0)) == SIGN_EXTEND
		  || GET_CODE(XEXP(SET_SRC(exp),1)) == ZERO_EXTEND
		  || GET_CODE(XEXP(SET_SRC(exp),1)) == SIGN_EXTEND)) {
	    CC_STATUS_INIT;
	    return;
	  }
	  break;
	  
	case ASHIFT:
	  if (GET_CODE(XEXP(SET_SRC(exp),1)) != CONST_INT)
	    break;
	  /* Fall into... */
	case NOT:
	case XOR: 
	  if (GET_MODE(SET_DEST(exp)) == SImode) 
	    break;
	  /* Else fall down into... */
	case DIV:
	case MOD:
	case MULT: 
	case UMIN:
	case FFS:
	case ABS:
	  CC_STATUS_INIT;
	  return;

	case CONST_INT:
	  /* Check for quickened ints;
	     255-31..255 for byte, &&
	     65535-31..65535 for word. */
	  if (GET_MODE(SET_DEST(exp)) != SImode
	      && !CONST_OK_FOR_LETTER_P(INTVAL(SET_SRC(exp)),'I')
	      /*&& get_attr_slottable(insn) == SLOTTABLE_YES*/) {
	    CC_STATUS_INIT;
	    return;
	  }
	  break;

        case LABEL_REF:
	case SYMBOL_REF:
	case REG:
	case MEM:
	case CONST:
	  /* Some are not really useful, but what the ... let them */
	  /* through too. So fall down into...  */
	case SIGN_EXTEND:
	case ZERO_EXTEND:
	case ASHIFTRT:
	case LSHIFTRT:
	case NEG:
	  break;		/* Ok for all modes. */


	  /* Sne etc. dont change c-codes. */
	case NE:
	case EQ:
	case GE:
	case GT:
	case LT:
	case LE:
	case GEU:
	case GTU:
	case LEU:
	case LTU:
	  if (XEXP(SET_SRC(exp),0) == cc0_rtx)
          {
            /* Better check if we "set" anything that overlaps. */
            if (cc_status.value1
                && my_reg_overlap_mentioned_p(SET_DEST(exp),
                                              cc_status.value1))
              cc_status.value1 = 0;
            
            if (cc_status.value2
                && my_reg_overlap_mentioned_p(SET_DEST(exp),
                                              cc_status.value2))
              cc_status.value2 = 0;
            
	    return;
          }
	  CC_STATUS_INIT;
	  return;
	  break;

	default:		/* If any condition isnt listed above, */
				/* then its really a bug */
	  debug_rtx(insn);
	  fatal("Internal: Condition code status not defined for above insn");
	  break;
	}
	
	/* Arithmetic operations DO set overflow, just not correct to
	   eliminate test insns on result in all cases. */
	switch (GET_CODE(SET_SRC(exp))) {
	case PLUS: case MINUS: case NEG: case ABS: case UMIN:
	  cc_status.flags = CC_NO_OVERFLOW;
	  break;

	default:
	  cc_status.flags = 0;
	  break;
	}

	cc_status.value1
	  = GET_CODE(SET_DEST(exp)) == STRICT_LOW_PART
	    ? XEXP(SET_DEST(exp),0) : SET_DEST(exp);
	cc_status.value2
	  = (my_reg_overlap_mentioned_p(GET_CODE(SET_DEST(exp)) != STRICT_LOW_PART
				     ? SET_DEST(exp) : XEXP(SET_DEST(exp),0),
				     SET_SRC(exp)))
	    ? 0 : SET_SRC(exp);
	return;
      }
      
    /* It wasnt a register being set, then probably mem.  */ 
    if (GET_CODE (SET_DEST (exp)) == MEM
        || (GET_CODE (SET_DEST (exp)) == STRICT_LOW_PART
            && GET_CODE (XEXP(SET_DEST (exp),0)) == MEM)) {
      /* When SET to MEM, then no cc is changed (except if reg mentioned) */
      if ((cc_status.value1
	   && my_reg_overlap_mentioned_p(SET_DEST(exp),cc_status.value1)))
	cc_status.value1 = 0;
      if ((cc_status.value2
	   && my_reg_overlap_mentioned_p(SET_DEST(exp),cc_status.value2)))
	cc_status.value2 = 0;
      return;
    } 

    /* Not SET to pc, cc, reg or mem. Then what? */
    debug_rtx(insn);
    debug_rtx(exp);
    fatal("Previous \'SET\' not recognizable");
  }    
  
  /* Identify side-effect addressing to reg.
     Only move.S [rx=ry+(reg.S|offs)],rz is identified. */
  if (GET_CODE(exp) == PARALLEL) {
    if (GET_CODE(XVECEXP(exp,0,0)) == SET
	&& REG_P(XEXP(XVECEXP(exp,0,0),0))
	&& GET_CODE(XEXP(XVECEXP(exp,0,0),1)) == MEM
	&& GET_CODE(XVECEXP(exp,0,1)) == SET
	&& REG_P(XEXP(XVECEXP(exp,0,1),0))) {
      /* For "move.S [rx=ry+o],rz", say flags reflect
         value1=rz and value2=[rx] */
      cc_status.value1 = XEXP(XVECEXP(exp,0,0),0);
      cc_status.value2 = gen_rtx(MEM,GET_MODE(XEXP(XVECEXP(exp,0,0),0)),
				 XEXP(XVECEXP(exp,0,1),0));
      cc_status.flags = 0;
      /* Huh? sideeffect changed destination register?  */
      if (my_reg_overlap_mentioned_p(cc_status.value1,cc_status.value2))
	fatal("Internal: sideeffect-insn affecting main effect");
      return;
    }
    CC_STATUS_INIT;
    return;
  }

  if (GET_CODE(exp) == RETURN) {
    /* No: We may move scc insns into delay slots if not CC_INIT. */
#if 0
    CC_STATUS_INIT;
#endif
    return;
  }

  /* Nop */
  if (GET_CODE(exp) == CONST_INT && exp == const0_rtx)
    return;
  
  /* Well, besides SET & PARALLELs I dunno what. SEQUENCES?
     They shouldn't appear here. */
  debug_rtx(insn);
  debug_rtx(exp);
  fatal("Previous \'CC-INSN\' not recognizable");
}

#if 0
/* NOT USED */
/*#**************************************************************************
*#
*#  FUNCTION NAME : not_redundant_test
*#
*#  PARAMETERS    : insn : the body of the insn.
*#
*#  RETURNS       : an integer reflecting  = 0 : this insn is a
*#                  redundant test insn. Else: not.
*#
*#  DESCRIPTION   : looks into the pattern and previous insns to see
*#                  if this (test) insn really is redundant.Used to
*#                  stop redundant test insns from going into
*#                  delay-slots, from where they cannot be eliminated. 
*# 
*# NOTE: THIS IS UNDER TEST.  I really dont know how to stop
*# gcc from moving redundant test insns into delayed-branch slots.
*# NOT CURRENTLY USED.
*#
*# Returns 0 if the insn is one of an adjacent pair:
*# (SET x y)
*# (SET cc0 [xy])
*# where [xy] is one of x or y.
*#---------------------------------------------------------------------------
*#
*#  HISTORY
*#
*#  DATE     NAME                  CHANGES
*#  ----     ----                  -------
*#  920625   HP                    Init. Realized that this was too
*#                                 much for a macro. 
*#  920814   HP                    Initial adoption to SW standard
*#
*#************************************************************************#*/
int
not_redundant_test(insn)
     rtx insn;
{
  rtx tem = 0;

  /* Func sets_cc0_p checks whether this is a test insn. If neither that
     or the next insn sets cc0 then this insn may be scheduled.  */
  if (!sets_cc0_p(PATTERN(insn))
      && (tem = next_nonnote_insn(insn)) /* Maybe no next.. */
      && (GET_CODE(tem) != INSN || GET_CODE(PATTERN(tem)) != SET
	  || !sets_cc0_p(PATTERN(tem))))
    return 1;

  /* If looks like this:
     (SET x y) <- insn
     (TEST [xy]) <- tem
     then swap tem && insn.  */
  if (tem && !sets_cc0_p(PATTERN(insn))) {
    rtx tem2 = tem;
    tem = insn;
    insn = tem2;
  } else /* Just find tem. */
    tem = prev_nonnote_insn(insn);

  /* This (insn) is a test insn. Check whether the insn before (i.e tem)
   * handles the expression tested (mem or reg). If it does, then
   * assume that cc is set correctly, so the test insn will be removed.
   *  This will fail for some arithmetic insns, but we assume they are few.
   */
  if (tem == 0 || GET_CODE(tem) != INSN || GET_CODE(PATTERN(tem)) != SET)
    return 1;			/* It was not an ordinary SET insn */

  /* Do a subset of the check done when removing redundant test insns
     (in final.c). This version is allowed to fail, but shouldnt do so
     on a regular basis. We check whether the lvalue or the rvalue of
     the SET insn is equal to the rvalue of the test insn.
     This fails for side-effect [rl]values and volatile references.

      The effect of the failure is that any not-redundant test insn
     with a SET insn before, whose [lr]value looks like the test
     will not be put in a delayed-branch slot. */
  if (rtx_equal_p(XEXP(PATTERN(tem),0),XEXP(PATTERN(insn),1))
      || rtx_equal_p(XEXP(PATTERN(tem),1),XEXP(PATTERN(insn),1)))
    return 0;

  return 1;
}
#endif
  
/*#**************************************************************************
*#
*#  FUNCTION NAME : simple_epilogue
*#
*#  PARAMETERS    : none. Values taken from global variables.
*#  RETURNS       : an integer != 0 if "ret" or "jmp [sp+]" is
*#                  sufficient for exiting from this function
*#
*#  DESCRIPTION   : Return != 0 if it is appropriate to emit `ret'
*#                  instructions in the body of a function.  Do this
*#                  only if the epilogue is simple, needing a couple
*#                  of insns.  Prior to reloading, we can't tell how
*#                  many registers must be saved, so return 0 then.   
*#
*#---------------------------------------------------------------------------
*#
*#  HISTORY
*#
*#  DATE     NAME                  CHANGES
*#  ----     ----                  -------
*#  920625   HP                    Init. Realized that this was too
*#                                 much for a macro. 
*#  920814   HP                    Initial adoption to SW standard
*#  930504   HP                    Now also true if a single movem [sp+],r
*#                                 is sufficient.
*#
*#************************************************************************#*/
int
simple_epilogue ()
{
  int regno;
  int reglimit = STACK_POINTER_REGNUM;
  int lastreg = -1;

  /* Sorry, we don't know what the user has in mind for the prologue/epilogue
     if he don't want us to output it.  */
  if (! reload_completed || frame_pointer_needed || get_frame_size () != 0
      || current_function_pretend_args_size
      || current_function_args_size
      || current_function_outgoing_args_size
      || !TARGET_PROLOGUE_EPILOGUE)
    return 0;

  for (regno = 0; regno < reglimit; regno++)
    if ((regs_ever_live[regno] && ! call_used_regs[regno])) {
      if (lastreg != regno-1)
	return 0;
      lastreg = regno;
    }

  return 1;
}

/*#**************************************************************************
*#
*#  FUNCTION NAME : jvm_address_cost
*#
*#  PARAMETERS    : x : an address rtx.
*#  RETURNS       : an integer which reflects the cost of x.
*#  DESCRIPTION   : Compute the cost of address mode x. Dont need to
*#                  look for bad address modes, the cost is irrelevant then.
*#
*#---------------------------------------------------------------------------
*#
*#  HISTORY
*#
*#  DATE     NAME                  CHANGES
*#  ----     ----                  -------
*#  920625   HP                    Init. Realized that this was too
*#                                 much for a macro. 
*#  920814   HP                    Initial adoption to SW standard
*#  930515   HP                    Changed to better CSE of constant addresses
*#                                 and a consequent measure for cost.
*#
*#************************************************************************#*/
int 
jvm_address_cost(x)
     rtx x;
{
  /* For measurement I use 1+(the number of cycles)/2 needed HP 930515. */
  /* The cheapest addressing modes get 1.  */
  if (BASE_OR_AUTOINCR_P(x))
    return 1;

  /* An indirect mem must be a dip. This means 2 bytes extra for code,
     and 4 bytes extra for memory fetch, i.e 1+2+1 = 4 */
  /* Add 2 for an indirect mem. That would be a dip prefix.  */
  if (GET_CODE(x) == MEM)
    return (2+4)/2+1;

  /* Assign a sligtly higher cost for const+int than for const,
     as they may be cse:d into [r+int] which is MUCH cheaper than
     [const+int]. */ 
  if (GET_CODE(x) == CONST && GET_CODE(XEXP(x,0)) == PLUS)
    return (2+4)/2+1+1;

  /* Assume 2+4 for a single constant; dword. This means an extra
     dip + 4 bytes of constant. */
  if (CONSTANT_P(x))
    return (2+4)/2+1;

  /* Check biap and bdap prefixes. */
  if (GET_CODE(x) == PLUS) {
    rtx tem1 = XEXP(x,0);	/* Probably reg. */
    rtx tem2 = XEXP(x,1);	/* BIAP or const or [r+],[r]. */

    /* Biap is 2 extra bytes. Always is tem1 because of insn canonicalzn. */
    if (GET_CODE(tem1) == MULT && BIAP_INDEX_P(tem1))
      return 2/2+1;

    /* Bdap quick is 2 extra bytes. */
    if (GET_CODE(tem2) == CONST_INT
	&& INTVAL(tem2) < 128 && INTVAL(tem2) >= -128)
      return 2/2+1;

    /* Bdap -32768..32767 is like bdap with 2 extra bytes. */
    if (GET_CODE(tem2) == CONST_INT
	&& CONST_OK_FOR_LETTER_P(INTVAL(tem2),'L'))
      return (2+2)/2+1;

    /* Bdap with some other const is 2 bytes extra. */
    if (CONSTANT_P(tem2))
      return (2+2+2)/2+1;

    /* Bdap with something indirect should have a higher cost than
       biap w register. Something like (2+1)/2+1, but lets stick to the
       same as bdap -32768..32767 */
    /* Dont need to check it, its the only one left. */
    return (2+2)/2+1;
  }

  /* What else? */
  return 10;
}

/*#**************************************************************************
*#
*#  FUNCTION NAME : side_effect_mode_ok
*#
*#  PARAMETERS    : code : PLUS or MULT
*#                  ops  : an array of rtx:es. lreg, rreg, rval,
*#                         multop and other_op are indexes into this,
*#                         or -1 if they are not applicable. 
*#                  lreg : the register to get the side-effect 
*#                  rreg : one register in the side-effect expression
*#                  rval : the other register, or an int.
*#                  multop : an integer to multiply rval with.
*#                  other_op : one of the entities of the main effect,
*#                             whose mode we must consider.
*#  RETURNS       : an integer which is != 0 if the implied
*#                  side-effect is ok.
*#  DESCRIPTION   : Check various objections to the side-effect.  Used
*#                  in the test-part of an anonymous insn describing
*#                  an insn with a possible side-effect.
*#
*#---------------------------------------------------------------------------
*#
*#  HISTORY
*#
*#  DATE     NAME                  CHANGES
*#  ----     ----                  -------
*#  920625   HP                    Init. Realized that this was too
*#                                 much for a macro. 
*#  920814   HP                    Initial adoption to SW standard
*#  940328   HP                    Bugfix; obviously never checked
*#                                 (after swapping with val_rtx) that
*#                                 reg_rtx really IS a reg ! 
*#  950517   HP                    Do not accept frame_pointer_rtx as
*#                                 any operand.
*#
*#************************************************************************#*/
int
side_effect_mode_ok(code,ops,lreg,rreg,rval,multop,other_op)
     enum rtx_code code;
     rtx *ops;
     int lreg,rreg,rval,multop,other_op;
{
  /* Find what value to multiply with, in case of rx=ry+rz*n. */
  int mult = multop < 0 ? 1 : INTVAL(ops[multop]);

  rtx reg_rtx = ops[rreg];
  rtx val_rtx = ops[rval];

  /* The operands may be swapped. Canonicalize them in reg_rtx and val_rtx,
     where reg_rtx always is a reg (for this constraint to match). */
  if (!BASE_P(reg_rtx))
    reg_rtx = val_rtx, val_rtx = ops[rreg];

  /* Must check that reg_rtx really is a reg! */
  if (!BASE_P(reg_rtx))
    return 0;

  /* The mult expression may be hidden in lreg. */
  if (GET_CODE(val_rtx) == MULT) {
    mult = INTVAL(XEXP(val_rtx,1));
    val_rtx = XEXP(val_rtx,0);
    code = MULT;
  }

  /* First check the "other operand". */
  if (other_op >= 0) {
    if (GET_MODE_SIZE(GET_MODE(ops[other_op])) > UNITS_PER_WORD)
      return 0;

    /* Check if the lvalue register is the same as the "other operand". */
    if (BASE_P(ops[lreg]) && BASE_P(ops[other_op])
	&& REGNO(ops[lreg]) == REGNO(ops[other_op])
	|| rtx_equal_p(ops[other_op],ops[lreg]))
      return 0;

  }

  /* Never allow this if -mno-split. */
  if (!TARGET_SPLIT)
    return 0;

  /* Do not accept frame_pointer_rtx as any operand */
  if (ops[lreg] == frame_pointer_rtx || ops[rreg] == frame_pointer_rtx
      || ops[rval] == frame_pointer_rtx
      || other_op >= 0 && ops[other_op] == frame_pointer_rtx)
    return 0;

  if (code == PLUS && !BASE_P(val_rtx)) {

    /* Check for too big values.  */
    /* No too big values anymore 930430 */
#if 0
    if (!CONST_OK_FOR_LETTER_P(INTVAL(val_rtx),'L'))
      return 0;
#endif
    /* Do not allow rx=rx+n if we can use normal add or sub with same size. */
    if (rtx_equal_p(ops[lreg],reg_rtx) && GET_CODE(val_rtx) == CONST_INT
	&& (INTVAL(val_rtx) <= 63 && INTVAL(val_rtx) >= -63))
      return 0;

    /* Some other cases now, like [r(+)?].[bwd] and const */
    if (CONSTANT_P(val_rtx))
      return 1;

    if (GET_CODE(val_rtx) == MEM && BASE_OR_AUTOINCR_P(XEXP(val_rtx,0)))
      return 1;

    if (GET_CODE(val_rtx) == SIGN_EXTEND
	&& GET_CODE(XEXP(val_rtx,0)) == MEM
	&& BASE_OR_AUTOINCR_P(XEXP(XEXP(val_rtx,0),0)))
      return 1;
    
    /* Something went wrong. */
    return 0;

  } else if (code == MULT
	     || (code == PLUS && BASE_P(val_rtx))) {

    /* Do not allow rx=rx+ry.S.  That doesnt give better code. */
    if (rtx_equal_p(ops[lreg],reg_rtx)
	|| (mult == 1 && rtx_equal_p(ops[lreg],val_rtx)))
      return 0;

    /* Do not allow bad multiple values. */
    if (mult != 1 && mult != 2 && mult != 4)
      return 0;

    /* Only allow r+r.s */
    if (!BASE_P(reg_rtx))
      return 0;

    /* Here if all seems ok. (Add all checks above this line). */
    return 1;
  } 
  
  /* Here on error (bad code). */
  fatal("Internal: side_effect_mode_ok with bad operands");
}

/*#**************************************************************************
*#
*#  FUNCTION NAME : same_ref_as_saved
*#
*#  PARAMETERS    : r : a register rtx.
*#                  x : an address rtx.
*#  RETURNS       : an rtx to substitute for x, or x.
*#  DESCRIPTION   : Check if we have previously saved a reg rtx with
*#                  the same symbol_ref or label_ref as x.  Then we
*#                  can return a cheaper address than x by returning
*#                  the saved one plus a constant that reflects the
*#                  difference.  This routine is used in the '%R'
*#                  output format to show where we can possibly
*#                  replace with a cheaper address mode.
*#                   This function should not be needed at all;
*#                  -fforce-addr should do the work.  For unknown
*#                  reasons it doesnt always do a good work.
*#                   This is an attempt to patch that together.
*#                  As a magical side-effect, save the rtx
*#                  if it is a const_ref. The register r is saved.
*#
*#---------------------------------------------------------------------------
*#
*#  HISTORY
*#
*#  DATE     NAME                  CHANGES
*#  ----     ----                  -------
*#  920625   HP                    Init. Realized that this was too
*#                                 much for a macro. 
*#  920814   HP                    Initial adoption to SW standard
*#  940221   HP                    Bugfix; the rtx:es in "saveregs[]"
*#                                 will be overwritten from one
*#                                 function to another.   Check added
*#                                 to see if we are still in the same
*#                                 function. 
*#
*#************************************************************************#*/
rtx
same_ref_as_saved(r,x)  
     rtx r,x;
{
  rtx tem,tem2;

  static int which_assign=0;
  static rtx saveregs[2] = {0, 0};

  /* Use these to check when we come to a new function.
     Then we have to forget everything explicitly, because all saved
     rtx:es may be garbled. */ 
  static char *last_name = NULL;

  if (!TARGET_EXTRA_CSE)
    return x;

  /* Check if we changed function scope; then all rtx:es are lost,
     e.g. those saved in "saveregs". */
  if (last_name == NULL
      || my_current_function_name == NULL /* Context may be lost. */
      || strcmp(last_name, my_current_function_name))
    {
      if (last_name != NULL)
        free(last_name);
      last_name = my_current_function_name == NULL
        ? NULL : xstrdup(my_current_function_name);
      saveregs[0] = 0; saveregs[1] = 0; which_assign = 0;
    }

  /*
    Check if this is a new one to save. At least gcc is smart enough
    to cse EXACTLY same values, so we have nothing to win by
    checking if we could return a register.
    */
  if (r != 0			/* Only true in call from movsi/8 */
      /* Check if this is a const_ref */
      && (tem = get_real_related_value(x)) != 0
      && (GET_CODE(tem) == SYMBOL_REF
	  || GET_CODE(tem) == LABEL_REF)
      /* Check if this const_ref wasnt same as the previous saved one. */
      && (saveregs[1-which_assign] == 0
	  || tem != get_real_related_value(saveregs[1-which_assign])
	  /* Check if previous set is not active any more. */
	  || (tem2 = reg_set_last(saveregs[1-which_assign],
				  final_saved_insn)) == 0
	  || get_real_related_value(tem2) != tem)) { 
    
    /* Dont be unoptimized by consecutive assigns to same reg. */
    if (saveregs[which_assign] == r) 
      which_assign = 1-which_assign;
    
    /* Save which register was assigned to. */
    saveregs[1-which_assign] = r;
    which_assign = 1-which_assign;

    return x;
  }

  /* To here when we try to replace. */

  /* Other rtx:es than memory may come here. */
  if (GET_CODE(x) != MEM)
    return x;
  tem = XEXP(x,0);

  /* First, check if it is a const_ref */
  if ((tem = get_real_related_value(tem)) != 0
      && (GET_CODE(tem) == SYMBOL_REF
	  || GET_CODE(tem) == LABEL_REF)) {
    
    rtx replace_reg, last_val;

    /* Then check if it is equal to the value last assigned to one
       of the saved regs.  We may have changed scope.
       */
    if (((replace_reg = saveregs[0]) != 0
	 && const_ref_operand((last_val
			       = reg_set_last(replace_reg,
					      final_saved_insn)),SImode)
	 && get_real_related_value(last_val) == tem)
	|| ((replace_reg = saveregs[1]) != 0
	    && const_ref_operand((last_val
				  = reg_set_last(replace_reg,
						 final_saved_insn)),SImode)
	    && get_real_related_value(last_val) == tem)) {
      rtx new = gen_rtx(MEM,GET_MODE(x),plus_constant(replace_reg,
					      get_integer_term(XEXP(x,0))-
					      get_integer_term(last_val)));
      if (TARGET_PDEBUG) {
	debug_rtx(x);
	debug_rtx(new);
	fprintf(stderr,
		"Extra cse: The first rtx-address was buffered %s",
		"and replaced with the latter\n");
      }
      return new;
    }
  } 

  return x;
}

/*#**************************************************************************
*#
*#  FUNCTION NAME : get_real_related_value
*#
*#  PARAMETERS    : x : an address rtx.
*#  RETURNS       : an rtx which is the main part of x; a symbol_ref
*#                  or label_ref. 
*#  DESCRIPTION   : Replacement for get_related_value, which doesn't
*#                  work properly on pure symbol_refs and label_refs.
*#
*#---------------------------------------------------------------------------
*#
*#  HISTORY
*#
*#  DATE     NAME                  CHANGES
*#  ----     ----                  -------
*#  920625   HP                    Init. Realized that this was too
*#                                 much for a macro. 
*#  920814   HP                    Initial adoption to SW standard
*#
*#************************************************************************#*/
static rtx
get_real_related_value(x)
     rtx x;
{
  return (GET_CODE(x) == SYMBOL_REF || GET_CODE(x) == LABEL_REF) ? x
    : get_related_value(x);
}

/*#**************************************************************************
*#
*#  FUNCTION NAME : redundant
*#
*#  PARAMETERS    : insn : the body of the insn.
*#
*#  RETURNS       : an integer reflecting  != 0 : this insn is a
*#                  redundant test insn. Else: not.
*#
*#  DESCRIPTION   : looks into the pattern and previous insns to see
*#                  if this insn really is redundant. Used to
*#                  stop redundant insns from going into
*#                  delay-slots, from where they cannot be eliminated. 
*#                  Try to see if the insn is redundant, so not to
*#                  move it into a delay-slot. The way signed div and
*#                  mod are expanded, a dead insn may end up in a
*#                  delayed-slot if that insn sets a reg that is part
*#                  of a return reg.  But we know of this case, and
*#                  when the previous insn is a divmod whose regs are
*#                  not mentioned in this insn, then we can reject this 
*#                  insn and rest assured that the divmod will be
*#                  placed in the delay-slot. 
*# 
*# NOTE: THIS IS UNDER TEST.  I really dont know how to stop
*# gcc from moving redundant insns into delayed-branch slots.
*# NOT CURRENTLY USED.
*#
*#---------------------------------------------------------------------------
*#
*#  HISTORY
*#
*#  DATE     NAME                  CHANGES
*#  ----     ----                  -------
*#  920625   HP                    Init. Realized that this was too
*#                                 much for a macro. 
*#  920814   HP                    Initial adoption to SW standard
*#
*#************************************************************************#*/
int
redundant(insn)
     rtx insn;
{
  rtx tem;

  return 0;
#if 0
  return (GET_CODE(PATTERN(insn)) == SET
	  && REG_P(SET_DEST(PATTERN(insn)))
	  && call_used_regs[REGNO(SET_DEST(PATTERN(insn)))]
	  && (tem = prev_real_insn(insn)) != 0
	  && INSN_CODE(tem) == CODE_FOR_udivmodsi4);
#endif
}
/*#**************************************************************************
*#
*#  FUNCTION NAME : output_block_move()
*#
*#  PARAMETERS    : operands : an rtx [].
*#  RETURNS       : nothing
*#  DESCRIPTION   : Outputs move instructions to inline small block-moves
*#
*#---------------------------------------------------------------------------
*#
*#  HISTORY
*#
*#  DATE     NAME                  CHANGES
*#  ----     ----                  -------
*#  920815   HP                    Initial adoption to SW standard
*#  940207   HP                    Bugfix; PUT_MODE() interferes with
*#                                 other insns.  Note that this effect
*#                                 is desired in adjust_ops(), but
*#                                 definitely not here.
*#
*#************************************************************************#*/
void
output_block_move(operands)
     rtx *operands;
{
  /* A simplified move_by_pieces_1 */
  int i;
  int block_size = INTVAL(operands[2]);
  static enum machine_mode mode[] = {SImode, HImode, QImode, VOIDmode};
  
  for (i = 0; mode[i] != VOIDmode; i++)
  {
    int size = GET_MODE_SIZE (mode[i]);
    
    while (block_size >= size)
    {
      /* It seems PUT_MODE() is bad to use, since operands[] may be
         shared, which results in modifying the sizes of operands
         of other insns. */
      switch(size)
      {
      case 4:
        output_asm_insn("move.d [%1+],%4\n\tmove.d %4,[%0+]", operands);
        break;
      case 2:
        output_asm_insn("move.w [%1+],%4\n\tmove.w %4,[%0+]", operands);
        break;
      case 1:
        output_asm_insn("move.b [%1+],%4\n\tmove.b %4,[%0+]", operands);
        break;
            
      default:
        output_asm_insn("move.??? [%1+],%4\n\tmove.??? %4,[%0+]", operands);
      }
      block_size -= size;
    }
  }
}

/*#**************************************************************************
*#
*#  FUNCTION NAME : adjust_ops
*#
*#  PARAMETERS    : x : an insn rtx.
*#  RETURNS       : nothing
*#  DESCRIPTION   : Adjusts the mode of any operands in the insn that may be
*#                  VOIDmode to the mode of the other operand.
*#
*#---------------------------------------------------------------------------
*#
*#  HISTORY
*#
*#  DATE     NAME                  CHANGES
*#  ----     ----                  -------
*#  920815   HP                    Initial adoption to SW standard
*#
*#************************************************************************#*/
static void fix_op();

void
adjust_ops(x)
     rtx x;
{
  if (GET_CODE(x) == PARALLEL) {
    int i;
    for (i = 0; i < XVECLEN(x,0); i++)
      adjust_ops(XVECEXP(x,0,i));
    return;
  }

  if (GET_CODE(x) == SET
      && XEXP(x,0) != cc0_rtx) {
    fix_op(x);
    adjust_ops(XEXP(x,1));
    return;
  }

  switch(GET_RTX_CLASS(GET_CODE(x))) {
  case 'i':
    adjust_ops(PATTERN(x));
    return;
  case 'c': case '2':
    fix_op(x);
    return;

  case '1':
    adjust_ops(XEXP(x,0));
    return;
  }
}

/*
 * Subroutine to adjust_ops
 */
static void
fix_op(x)
     rtx x;
{
  if (GET_MODE(XEXP(x,0)) != GET_MODE(XEXP(x,1))) {
    if (GET_MODE(XEXP(x,0)) == VOIDmode
	&& GET_CODE(XEXP(x,0)) != CONST_INT
	&& GET_CODE(XEXP(x,0)) != CONST_DOUBLE)
      PUT_MODE(XEXP(x,0),GET_MODE(XEXP(x,1)));
    else if (GET_MODE(XEXP(x,1)) == VOIDmode
	     && GET_CODE(XEXP(x,1)) != CONST_INT
	     && GET_CODE(XEXP(x,1)) != CONST_DOUBLE)
      PUT_MODE(XEXP(x,1),GET_MODE(XEXP(x,0)));
    else if (GET_CODE(XEXP(x,1)) != CONST_INT
	     && GET_CODE(XEXP(x,1)) != CONST_DOUBLE
	     && GET_CODE(XEXP(x,0)) != CONST_INT
	     && GET_CODE(XEXP(x,0)) != CONST_DOUBLE)
      {
	if (GET_MODE_SIZE(GET_MODE(XEXP(x,0)))
	    < GET_MODE_SIZE(GET_MODE(XEXP(x,1))))
	  PUT_MODE(XEXP(x,1),GET_MODE(XEXP(x,0)));
	else if (GET_MODE_SIZE(GET_MODE(XEXP(x,0)))
		 > GET_MODE_SIZE(GET_MODE(XEXP(x,1))))
	  PUT_MODE(XEXP(x,0),GET_MODE(XEXP(x,1)));
	else {
	  debug_rtx(x);
	  fatal("Internal: above has different modes in operands");
	}
      }
  }

  /* Adjust all operands to small modes so they fit.
     In some cases there is an added (1 << GET_MODE_BITSIZE(x)) to an
     operand.
      Note that this only checks operands that are positive.  We may
      have to do the same for negative fuckups later. */
  if (GET_MODE(XEXP(x,0)) != SImode
      && GET_MODE(XEXP(x,0)) != VOIDmode
      && GET_CODE(XEXP(x,1)) == CONST_INT
      && INTVAL(XEXP(x,1)) > (1 << GET_MODE_BITSIZE(GET_MODE(XEXP(x,0))))
      && TARGET_MODIFY_OPERANDS)
    XEXP(x,1) = gen_rtx(CONST_INT, VOIDmode,
			INTVAL(XEXP(x,1))
			% (1 << GET_MODE_BITSIZE(GET_MODE(XEXP(x,0)))));
    
}

/* reg_overlap_mentioned_p(x,in) does not handle the case where the
   operands are strict_low_parts.  This function takes care of that
   for THIS module */
static int
my_reg_overlap_mentioned_p(x, in)
     rtx x, in;
{
  /* Well, we only strip the strict_low_parts of the operands, but
     this is conservative; you may get overlap indications where there
     is no overlap, but it is safe. */
  if (GET_CODE(x) == STRICT_LOW_PART)
    x = XEXP(x,0);

  if (GET_CODE(in) == STRICT_LOW_PART)
    in = XEXP(in,0);

  return reg_overlap_mentioned_p(x,in);
}

/*#**************************************************************************
*#
*#  FUNCTION NAME : my_deferred_string_added
*#
*#  PARAMETERS    : labelno : the number of the string label, as 12 in
*#                            "LC12"
*#                  str     : the string to be output, or NULL if the
*#                            string is not yet available
*#                  str_len : the length of the string (it is not
*#                            necessarily zero-terminated; most often
*#                            the zero is counted in. 
*#                  mark_used: 1 if we should mark the string as used,
*#                             0 if we do not know (it should only be added).
*#  RETURNS       : 1 if the string is in this table.
*#                  0 if not
*#  DESCRIPTION   : Adds strings (or really byte arrays) that seems to
*#                  be local, and maybe not used, into a database, to
*#                  be output later.  Also indicates whether a must be
*#                  output later, or if it just a waste of space.
*#                  
*#
*#---------------------------------------------------------------------------
*#
*#  HISTORY
*#
*#  DATE     NAME                  CHANGES
*#  ----     ----                  -------
*#  960415   HP                    Created
*#
*#************************************************************************#*/
int
my_deferred_string_added(labelno, str, str_len, mark_used, add_at_all)
     int labelno;
     char *str;
     int str_len;
     int mark_used;
     int add_at_all;
{
  int retval = mark_used;
  struct deferred_string_struct_type *ds;
  int i;

  /* Find the right hash table slot */
  for (ds = & deferred_strings[labelno % STR_HASHSIZE_MAX];
       ds->next != NULL && labelno != ds->labelno;
       ds = ds->next)
    ;


  /* This is the right slot.  Check if we have the right entry here */
  if (ds->labelno != labelno)
  {
    /* Were we just checking if this label was entered? */
    if (!add_at_all)
      return 0;

    /* Nope. Is it a valid entry, or can we use it directly? */
    if (ds->labelno != -1)
    {
      ds->next = malloc(sizeof(struct deferred_string_struct_type));
      if (ds->next == NULL)
        fatal("Cannot get enough virtual mem\n");
      ds = ds->next;
      ds->next = NULL;
    }
    ds->str = NULL;
    
    ds->labelno = labelno;
  }
  else
    /* If just checking whether this label was entered, return 1. */
    if (!add_at_all)
      return 1;

  if (str)
  {
    ds->str = malloc(str_len);
    if (ds->str == NULL)
      fatal("Cannot get enough virtual mem\n");
    memcpy(ds->str,str,str_len);
    ds->str_len = str_len;
  }

  ds->output_it |= mark_used;

  /* Indicate that it is in the table (at least now...) */
  return 1;
}
     
/*#**************************************************************************
*#
*#  FUNCTION NAME : my_output_deferred_strings
*#
*#  PARAMETERS    : file : the file where we will print the strings.
*#  RETURNS       : nothing
*#  DESCRIPTION   : Outputs strings marked for output and stored in
*#                  the local-string database
*#                  
*#
*#---------------------------------------------------------------------------
*#
*#  HISTORY
*#
*#  DATE     NAME                  CHANGES
*#  ----     ----                  -------
*#  960415   HP                    Created
*#  980116   HP                    Fixed a bug causing align-by-dword instead
*#                                 of by word.
*#************************************************************************#*/
void
my_output_deferred_strings(file)
     FILE *file;
{
  int i;
  struct deferred_string_struct_type *ds;
  struct deferred_string_struct_type *ds_next;

  /* So we can use ASM_OUTPUT_ASCII */
  my_inhibit_stringout = 0;

  /* This stuff should be in the text section, as it normally would. */
  text_section();

  for (i = 0; i < STR_HASHSIZE_MAX; i++)
  {
    for (ds = &deferred_strings[i]; ds != NULL; ds=ds_next)
    {
      /* If the string is not entered, then really was a local (const)
         struct which was output elsewhere.  Then we should treat is
         as if it was never entered in the table. */
      if (ds->output_it && ds->str != NULL)
      {
        if (TARGET_CONST_ALIGN)
        {
          /* Should maybe be CONSTANT_ALIGNMENT(), but then we need an
             rtx for the first argument, and we really know the
             alignment here without going up a level. */
          ASM_OUTPUT_ALIGN(file, (TARGET_SVINTO ? 2 : 1));
        }

        fprintf(file, "LC%d:\n",ds->labelno);

        if (ds->str != NULL)
        {
          ASM_OUTPUT_ASCII(file, ds->str, ds->str_len);
        }
      }

      free (ds->str);

      /* Ok, so it could have been less kludgy... */
      ds_next = ds->next;
      if (ds != &deferred_strings[i])
        free(ds);
    }

    deferred_strings[i].labelno = -1;
  }
}

/*#**************************************************************************
*#
*#  FUNCTION NAME : my_init_deferred_strings
*#
*#  PARAMETERS    : file : where stuff needs to be written
*#  RETURNS       : nothing
*#  DESCRIPTION   : Prepares tables and stuff for local string tracking
*#                  
*#
*#---------------------------------------------------------------------------
*#
*#  HISTORY
*#
*#  DATE     NAME                  CHANGES
*#  ----     ----                  -------
*#  960415   HP                    Created
*#
*#************************************************************************#*/
void
my_init_deferred_strings(file)
     FILE *file;
{
  int i;

  for (i = 0; i < STR_HASHSIZE_MAX; i++)
  {
    deferred_strings[i].labelno = -1;
    deferred_strings[i].next = NULL;
  }

}
     
/***************************** DEBUGGING ROUTINES *************************/

/*#**************************************************************************
*#
*#  FUNCTION NAME : debug_printf
*#
*#  PARAMETERS    : str : string to be printed
*#
*#  RETURNS       : nothing
*#
*#  DESCRIPTION   : print the supplied string to stderr
*#
*#---------------------------------------------------------------------------
*#
*#  HISTORY
*#
*#  DATE     NAME                  CHANGES
*#  ----     ----                  -------
*#  911022   RW                    Initial
*#
*#************************************************************************#*/
void debug_printf(str)
char *str;
{
  fprintf(stderr, str);
}

FILE *datasection=NULL;

void setup_datasection_now() {
  if (!datasection)
    datasection = fopen("global.s","w");
}

/*#**************************************************************************
*#
*#  FUNCTION NAME : override_options
*#
*#  PARAMETERS    : none
*#
*#  RETURNS       : nothing
*#
*#  DESCRIPTION   : Parse stuff in TARGET_OPTIONS to usable values.
*#
*#---------------------------------------------------------------------------
*#
*#  HISTORY
*#
*#  DATE     NAME                  CHANGES
*#  ----     ----                  -------
*#  980113   HP                    Initial
*#
*#************************************************************************#*/
void
override_options()
{
  if (jvm_max_stackframe_str)
    {
      jvm_max_stackframe = atoi (jvm_max_stackframe_str);
      if (jvm_max_stackframe < 0 || jvm_max_stackframe > 0x20000000)
	fatal ("-max-stackframe=%d is not usable, not between 0 and %d",
               jvm_max_stackframe, 0x20000000);
    }
}

/*
  Various small functions to replace macros.  Only called from a
  debugger. 
 */
enum  rtx_code get_code(x) rtx x; { return GET_CODE(x);}
char *get_mode(x) rtx x; { return GET_MODE_NAME(GET_MODE(x));}
rtx xexp(x,n) rtx x; int n; { return XEXP(x,n);}
int get_rtx_len(x) rtx x; { return GET_RTX_LENGTH(GET_CODE(x)); }
rtx Next_insn(insn) rtx insn; { return NEXT_INSN(insn);}
rtx Prev_insn(insn) rtx insn; { return PREV_INSN(insn);}

int aux_stack_align()
{ return TARGET_STACK_ALIGN ? 16 : 8; }
/* End of jvm.c (aux-output.c) */
