;;**************************************************************************
;; FILE NAME : md
;;
;; DESCRIPTION : This is the machine description for the Java Virtual 
;;		 Machine.  My basic strategy in making this machine
;;               description has been to ignore the stack based nature
;;               of the JVM.  Instead, I have taken the basic instructions
;;               that a 32 bit processor would have and implemented them
;;               with (usually) more than one JVM bytecode.
;;               
;;               For example, one would expect a three address processor 
;;               to have an instruction that can add two 32 bit registers
;;               together and store the result in a third register.  This
;;               instruction is implemented with the bytecodes:
;;               
;;                      iload 1   ; register 1
;;                      iload 2   ; register 2
;;                      iadd
;;                      istore 3  ; register 3
;;               
;;               For a lot of instructions we generate 4 bytecodes (for  
;;               some we generate a significant number more).  I justify
;;               this by noting that the majority of bytecode will be run
;;               by a Just-In-Time compiler which will have no trouble
;;               turning the above sequence into a single instruction on
;;               the target machine.  For other situations one can utilise
;;               a bytecode optimisation program such as BLOAT.
;;
;;		   - Trent Waddington 9/9/1999
;;
;;
;;------------------------------------------------------------------------
;;
;;**************************************************************************

;; This file is part of GNU CC.

;; GNU CC is free software; you can redistribute it and/or modify
;; it under the terms of the GNU General Public License as published by
;; the Free Software Foundation; either version 2, or (at your option)
;; any later version.

;; GNU CC is distributed in the hope that it will be useful,
;; but WITHOUT ANY WARRANTY; without even the implied warranty of
;; MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
;; GNU General Public License for more details.

;; You should have received a copy of the GNU General Public License
;; along with GNU CC; see the file COPYING.  If not, write to
;; the Free Software Foundation, 675 Mass Ave, Cambridge, MA 02139, USA.

;;- Instruction patterns.  When multiple patterns apply,
;;- the first one in the file is chosen.
;;-
;;- See file "rtl.def" for documentation on define_insn, match_*, et. al.
;;-
;;- cpp macro #define NOTICE_UPDATE_CC in file tm.h handles condition code
;;- updates for most instructions.


;
; Compare insns.
;

; These are compare and branch optimisations.. 
; A compare instruction is usually followed by a branch, on the JVM
; there are bytecodes that can do this all at once.. so I use them
;  - tw

; Now is a good a time as any to define the things below.  If this 
; looks completely foriegn to you, BAIL OUT NOW, because there's a
; lot going on here that is better explained in the GCC documentation.
; 
; The % operator 'K' I have used to select the way to print a constant.
; A constant can be loaded in a number of ways on the JVM and this is 
; the way to say "load the constant the best way you can".  See the 
; print_operand function in jvm.c
;  - tw.

(define_peephole
  [(set (cc0)
        (compare
         (match_operand:SI 0 "nonimmediate_operand" "r,i")
         (const_int 0)))
   (set (pc)
        (if_then_else (eq (cc0)
                          (const_int 0))
                      (label_ref (match_operand 1 "" ""))
                      (pc)))]
  ""
  "@
   iload %0\\n\\tifeq %l1\\n
   %K0\\n\\tifeq %l1\\n")

(define_peephole
  [(set (cc0)
        (compare
         (match_operand:SI 0 "nonimmediate_operand" "r,i")
         (const_int 0)))
   (set (pc)
        (if_then_else (ne (cc0)
                          (const_int 0))
                      (label_ref (match_operand 1 "" ""))
                      (pc)))]
  ""
  "@
   iload %0\\n\\tifne %l1\\n
   %K0\\n\\tifne %l1\\n")

(define_peephole
  [(set (cc0)
        (compare
         (match_operand:SI 0 "nonimmediate_operand" "r,i")
         (const_int 0)))
   (set (pc)
        (if_then_else (lt (cc0)
                          (const_int 0))
                      (label_ref (match_operand 1 "" ""))
                      (pc)))]
  ""
  "@
   iload %0\\n\\tiflt %l1\\n
   %K0\\n\\tiflt %l1\\n")

(define_peephole
  [(set (cc0)
        (compare
         (match_operand:SI 0 "nonimmediate_operand" "r,i")
         (const_int 0)))
   (set (pc)
        (if_then_else (gt (cc0)
                          (const_int 0))
                      (label_ref (match_operand 1 "" ""))
                      (pc)))]
  ""
  "@
   iload %0\\n\\tifgt %l1\\n
   %K0\\n\\tifgt %l1\\n")

(define_peephole
  [(set (cc0)
        (compare
         (match_operand:SI 0 "nonimmediate_operand" "r,i")
         (const_int 0)))
   (set (pc)
        (if_then_else (le (cc0)
                          (const_int 0))
                      (label_ref (match_operand 1 "" ""))
                      (pc)))]
  ""
  "@
   iload %0\\n\\tifle %l1\\n
   %K0\\n\\tifle %l1\\n")

(define_peephole
  [(set (cc0)
        (compare
         (match_operand:SI 0 "nonimmediate_operand" "r,i")
         (const_int 0)))
   (set (pc)
        (if_then_else (ge (cc0)
                          (const_int 0))
                      (label_ref (match_operand 1 "" ""))
                      (pc)))]
  ""
  "@
   iload %0\\n\\tifge %l1\\n
   %K0\\n\\tifge %l1\\n")


(define_peephole
  [(set (cc0)
        (compare
         (match_operand:SI 0 "nonimmediate_operand" "r,r,i,i")
         (match_operand:SI 1 "general_operand"     "r,i,r,i")))
   (set (pc)
        (if_then_else (eq (cc0)
                          (const_int 0))
                      (label_ref (match_operand 2 "" ""))
                      (pc)))]
  ""
  "@
   iload %0\\n\\tiload %1\\n\\tif_icmpeq %l2\\n
   iload %0\\n\\t%K1\\n\\tif_icmpeq %l2\\n
   %K0\\n\\tiload %0\\n\\tif_icmpeq %l2\\n
   %K0\\n\\t%K1\\n\\tif_icmpeq %l2\\n")

(define_peephole
  [(set (cc0)
        (compare
         (match_operand:SI 0 "nonimmediate_operand" "r,r,i,i")
         (match_operand:SI 1 "general_operand"     "r,i,r,i")))
   (set (pc)
        (if_then_else (ne (cc0)
                          (const_int 0))
                      (label_ref (match_operand 2 "" ""))
                      (pc)))]
  ""
  "@
   iload %0\\n\\tiload %1\\n\\tif_icmpne %l2\\n
   iload %0\\n\\t%K1\\n\\tif_icmpne %l2\\n
   %K0\\n\\tiload %0\\n\\tif_icmpne %l2\\n
   %K0\\n\\t%K1\\n\\tif_icmpne %l2\\n")

(define_peephole
  [(set (cc0)
        (compare
         (match_operand:SI 0 "nonimmediate_operand" "r,r,i,i")
         (match_operand:SI 1 "general_operand"     "r,i,r,i")))
   (set (pc)
        (if_then_else (lt (cc0)
                          (const_int 0))
                      (label_ref (match_operand 2 "" ""))
                      (pc)))]
  ""
  "@
   iload %0\\n\\tiload %1\\n\\tif_icmplt %l2\\n
   iload %0\\n\\t%K1\\n\\tif_icmplt %l2\\n
   %K0\\n\\tiload %0\\n\\tif_icmplt %l2\\n
   %K0\\n\\t%K1\\n\\tif_icmplt %l2\\n")

(define_peephole
  [(set (cc0)
        (compare
         (match_operand:SI 0 "nonimmediate_operand" "r,r,i,i")
         (match_operand:SI 1 "general_operand"     "r,i,r,i")))
   (set (pc)
        (if_then_else (gt (cc0)
                          (const_int 0))
                      (label_ref (match_operand 2 "" ""))
                      (pc)))]
  ""
  "@
   iload %0\\n\\tiload %1\\n\\tif_icmpgt %l2\\n
   iload %0\\n\\t%K1\\n\\tif_icmpgt %l2\\n
   %K0\\n\\tiload %0\\n\\tif_icmpgt %l2\\n
   %K0\\n\\t%K1\\n\\tif_icmpgt %l2\\n")

(define_peephole
  [(set (cc0)
        (compare
         (match_operand:SI 0 "nonimmediate_operand" "r,r,i,i")
         (match_operand:SI 1 "general_operand"     "r,i,r,i")))
   (set (pc)
        (if_then_else (ge (cc0)
                          (const_int 0))
                      (label_ref (match_operand 2 "" ""))
                      (pc)))]
  ""
  "@
   iload %0\\n\\tiload %1\\n\\tif_icmpge %l2\\n
   iload %0\\n\\t%K1\\n\\tif_icmpge %l2\\n
   %K0\\n\\tiload %0\\n\\tif_icmpge %l2\\n
   %K0\\n\\t%K1\\n\\tif_icmpge %l2\\n")

(define_peephole
  [(set (cc0)
        (compare
         (match_operand:SI 0 "nonimmediate_operand" "r,r,i,i")
         (match_operand:SI 1 "general_operand"     "r,i,r,i")))
   (set (pc)
        (if_then_else (le (cc0)
                          (const_int 0))
                      (label_ref (match_operand 2 "" ""))
                      (pc)))]
  ""
  "@
   iload %0\\n\\tiload %1\\n\\tif_icmple %l2\\n
   iload %0\\n\\t%K1\\n\\tif_icmple %l2\\n
   %K0\\n\\tiload %0\\n\\tif_icmple %l2\\n
   %K0\\n\\t%K1\\n\\tif_icmple %l2\\n")

; unsigned cmp/branch combos
; this is a mess because the guys at Sun decided that no-one needed
; unsigned branches (or registers for that matter).  Apparently they 
; are correcting this.  My solution is to convert the two 32 bit numbers
; to 64 bit numbers, do the comparison and branch on the 64 bit result.
;  - tw

(define_peephole
  [(set (cc0)
        (compare
         (match_operand:SI 0 "nonimmediate_operand" "r,r,i,i")
         (match_operand:SI 1 "general_operand"     "r,i,r,i")))
   (set (pc)
        (if_then_else (ltu (cc0)
                          (const_int 0))
                      (label_ref (match_operand 2 "" ""))
                      (pc)))]
  ""
  "@
   iload %0\\n\\ti2l\\n\\tldc2_w 4294967295\\n\\tland\\n\\tiload %1\\n\\ti2l\\n\\tldc2_w 4294967295\\n\\tland\\n\\tlcmp\\n\\tiflt %l2\\n
   iload %0\\n\\ti2l\\n\\tldc2_w 4294967295\\n\\tland\\n\\t%K1\\n\\ti2l\\n\\tldc2_w 4294967295\\n\\tland\\n\\tlcmp\\n\\tiflt %l2\\n
   %K0\\n\\ti2l\\n\\tldc2_w 4294967295\\n\\tland\\n\\tiload %0\\n\\ti2l\\n\\tldc2_w 4294967295\\n\\tland\\n\\tlcmp\\n\\tiflt %l2\\n
   %K0\\n\\ti2l\\n\\tldc2_w 4294967295\\n\\t%K1\\n\\ti2l\\n\\tldc2_w 4294967295\\n\\tland\\n\\tlcmp\\n\\tiflt %l2\\n")

(define_peephole
  [(set (cc0)
        (compare
         (match_operand:SI 0 "nonimmediate_operand" "r,r,i,i")
         (match_operand:SI 1 "general_operand"     "r,i,r,i")))
   (set (pc)
        (if_then_else (gtu (cc0)
                          (const_int 0))
                      (label_ref (match_operand 2 "" ""))
                      (pc)))]
  ""
  "@
   iload %0\\n\\ti2l\\n\\tldc2_w 4294967295\\n\\tland\\n\\tiload %1\\n\\ti2l\\n\\tldc2_w 4294967295\\n\\tland\\n\\tlcmp\\n\\tifgt %l2\\n
   iload %0\\n\\ti2l\\n\\tldc2_w 4294967295\\n\\tland\\n\\t%K1\\n\\ti2l\\n\\tldc2_w 4294967295\\n\\tland\\n\\tlcmp\\n\\tifgt %l2\\n
   %K0\\n\\ti2l\\n\\tldc2_w 4294967295\\n\\tland\\n\\tiload %0\\n\\ti2l\\n\\tldc2_w 4294967295\\n\\tland\\n\\tlcmp\\n\\tifgt %l2\\n
   %K0\\n\\ti2l\\n\\tldc2_w 4294967295\\n\\t%K1\\n\\ti2l\\n\\tldc2_w 4294967295\\n\\tland\\n\\tlcmp\\n\\tifgt %l2\\n")

(define_peephole
  [(set (cc0)
        (compare
         (match_operand:SI 0 "nonimmediate_operand" "r,r,i,i")
         (match_operand:SI 1 "general_operand"     "r,i,r,i")))
   (set (pc)
        (if_then_else (geu (cc0)
                          (const_int 0))
                      (label_ref (match_operand 2 "" ""))
                      (pc)))]
  ""
  "@
   iload %0\\n\\ti2l\\n\\tldc2_w 4294967295\\n\\tland\\n\\tiload %1\\n\\ti2l\\n\\tldc2_w 4294967295\\n\\tland\\n\\tlcmp\\n\\tifge %l2\\n
   iload %0\\n\\ti2l\\n\\tldc2_w 4294967295\\n\\tland\\n\\t%K1\\n\\ti2l\\n\\tldc2_w 4294967295\\n\\tland\\n\\tlcmp\\n\\tifge %l2\\n
   %K0\\n\\ti2l\\n\\tldc2_w 4294967295\\n\\tland\\n\\tiload %0\\n\\ti2l\\n\\tldc2_w 4294967295\\n\\tland\\n\\tlcmp\\n\\tifge %l2\\n
   %K0\\n\\ti2l\\n\\tldc2_w 4294967295\\n\\t%K1\\n\\ti2l\\n\\tldc2_w 4294967295\\n\\tland\\n\\tlcmp\\n\\tifge %l2\\n")

(define_peephole
  [(set (cc0)
        (compare
         (match_operand:SI 0 "nonimmediate_operand" "r,r,i,i")
         (match_operand:SI 1 "general_operand"     "r,i,r,i")))
   (set (pc)
        (if_then_else (leu (cc0)
                          (const_int 0))
                      (label_ref (match_operand 2 "" ""))
                      (pc)))]
  ""
  "@
   iload %0\\n\\ti2l\\n\\tldc2_w 4294967295\\n\\tland\\n\\tiload %1\\n\\ti2l\\n\\tldc2_w 4294967295\\n\\tland\\n\\tlcmp\\n\\tifle %l2\\n
   iload %0\\n\\ti2l\\n\\tldc2_w 4294967295\\n\\tland\\n\\t%K1\\n\\ti2l\\n\\tldc2_w 4294967295\\n\\tland\\n\\tlcmp\\n\\tifle %l2\\n
   %K0\\n\\ti2l\\n\\tldc2_w 4294967295\\n\\tland\\n\\tiload %0\\n\\ti2l\\n\\tldc2_w 4294967295\\n\\tland\\n\\tlcmp\\n\\tifle %l2\\n
   %K0\\n\\ti2l\\n\\tldc2_w 4294967295\\n\\t%K1\\n\\ti2l\\n\\tldc2_w 4294967295\\n\\tland\\n\\tlcmp\\n\\tifle %l2\\n")


;
; The normal compare patterns, from SI on.
; This just does a compare.  We load the two source operands, do a 
; subtract and store the result in '15' which I have declared is my 
; "flags" register.  Later this can be used to do a branch.  This hardly
; ever happens any more, because of the cmp/branch optimisations above.
;  - tw.
(define_insn "cmpsi"
  [(set (cc0)
        (compare
         (match_operand:SI 0 "nonimmediate_operand" "r,r,i,i")
         (match_operand:SI 1 "general_operand"     "r,i,r,i")))]
  ""
  "@
   iload %0\\n\\tiload %1\\n\\tisub\\n\\tistore 15\\n
   iload %0\\n\\t%K1\\n\\tisub\\n\\tistore 15\\n
   %K0\\n\\tiload %0\\n\\tisub\\n\\tistore 15\\n
   %K0\\n\\t%K1\\n\\tisub\\n\\tistore 15\\n"
  [])


;
; Move insns.
;

; No pattern for movdi is needed, gcc can split into movsi:s by
; itself.  

;
; Normal move patterns from SI on.
;
; This deserves explaination.  To move from register to register is easy,
; just load the source and store it to the destination.  Storing a
; constant into a register is just the same.  But it is when we get into 
; memory references that we run into the fun stuff.  Originally I was 
; implementing memory as a number of arrays with start addresses and doing
; a method call for every memory reference.  I profiled a memory intense
; program and it came out 60 times slower.  So I decided to move the
; memory references inline.  The first thing I had to do was merge all 
; the memory arrays into a single memory array, called "memory".  The next
; part was another headache caused by the lack of unsigned bytes.  Yes, 
; bytes are signed on the JVM.  So to load a 32 bit integer from memory
; one has to do:
;
;     reg =  memory[loc]<<24 
;          | memory[loc+1]<<16 
;          | memory[loc+2] << 8 
;	   | memory[loc+3]
;
; that is, if memory was an array of unsigned bytes, but it isn't.. so we
; would have to do:
;
;     reg =  (memory[loc]<0?256+memory[loc]:memory[loc])<<24 
;          | (memory[loc+1]<0?256+memory[loc+1]:memory[loc+1])<<16 
;          | (memory[loc+2]<0?256+memory[loc+2]:memory[loc+2])<<8 
;	   | (memory[loc+3]<0?256+memory[loc+3]:memory[loc+3]
;
; painful.. all those compares and branches.. how would we generate that?  
; My solution is make memory an array of int.  Then, when we load in the
; read only data at run time, we do the signed -> unsigned conversion
; before executing any code.  The result is:
;
;     reg =  memory[loc]<<24 
;          | memory[loc+1]<<16 
;          | memory[loc+2] << 8 
;	   | memory[loc+3]
;
; which, although still quite large, is a bit better.  Oh.. and we have
; to do quick a bit of stack trickery to keep the memory object and the 
; location on the stack at the right place.
;
; Stores to memory are done in a similar way:
;
;    memory[loc] = (reg>>24)&256
;    memory[loc+1] = (reg>>16)&256
;    memory[loc+2] = (reg>>8)&256
;    memory[loc+3] = reg&256
;
;   - tw


(define_insn "movsi"
  [(set
    (match_operand:SI 0 "general_operand"  "=r,r,r,m,m")
    (match_operand:SI 1 "general_operand"    "r,i,m,r,i"))]
  ""
  "@
   iload %1\\n\\tistore %0\\n
   %K1\\n\\tistore %0\\n
   aload_0\\n\\tgetfield %J0/memory [I\\n\\t%1\\n\\tdup2\\n\\tiaload\\n\\tbipush 8\\n\\tishl\\n\\tdup_x2\\n\\tpop\\n\\ticonst_1\\n\\tiadd\\n\\tdup2\\n\\tiaload\\n\\tbipush 16\\n\\tishl\\n\\tdup_x2\\n\\tpop\\n\\ticonst_1\\n\\tiadd\\n\\tdup2\\n\\tiaload\\n\\tbipush 8\\n\\tishl\\n\\tdup_x2\\n\\tpop\\n\\ticonst_1\\n\\tiadd\\n\\tiaload\\n\\tior\\n\\tior\\n\\tior\\n\\tistore %0\\n
   aload_0\\n\\tgetfield %J0/memory [I\\n\\t%0\\n\\tdup2\\n\\tiload %1\\n\\tbipush 24\\n\\tishr\\n\\tsipush 255\\n\\tiand\\n\\tiastore\\n\\ticonst_1\\n\\tiadd\\n\\tdup2\\n\\tiload %1\\n\\tbipush 16\\n\\tishr\\n\\tsipush 255\\n\\tiand\\n\\tiastore\\n\\ticonst_1\\n\\tiadd\\n\\tdup2\\n\\tiload %1\\n\\tbipush 8\\n\\tishr\\n\\tsipush 255\\n\\tiand\\n\\tiastore\\n\\ticonst_1\\n\\tiadd\\n\\tiload %1\\n\\tsipush 255\\n\\tiand\\n\\tiastore\\n
   aload_0\\n\\tgetfield %J0/memory [I\\n\\t%0\\n\\tdup2\\n\\t%K1\\n\\tbipush 24\\n\\tishr\\n\\tsipush 255\\n\\tiand\\n\\tiastore\\n\\ticonst_1\\n\\tiadd\\n\\tdup2\\n\\t%K1\\n\\tbipush 16\\n\\tishr\\n\\tsipush 255\\n\\tiand\\n\\tiastore\\n\\ticonst_1\\n\\tiadd\\n\\tdup2\\n\\t%K1\\n\\tbipush 8\\n\\tishr\\n\\tsipush 255\\n\\tiand\\n\\tiastore\\n\\ticonst_1\\n\\tiadd\\n\\t%K1\\n\\tsipush 255\\n\\tiand\\n\\tiastore\\n"
  [])

; this is the half word instruction.  Same as above except we only have to 
; do 2 array references per memory ref/store.
;  - tw

(define_insn "movhi"
  [(set
    (match_operand:HI 0 "general_operand"  "=r,r,r,m,m")
    (match_operand:HI 1 "general_operand"    "r,i,m,r,i"))]
  ""
  "@
   iload %1\\n\\tistore %0\\n
   %K1\\n\\tistore %0\\n
   aload_0\\n\\tgetfield %J0/memory [I\\n\\t%1\\n\\tdup2\\n\\tiaload\\n\\tbipush 8\\n\\tishl\\n\\tdup_x2\\n\\tpop\\n\\ticonst_1\\n\\tiadd\\n\\tiaload\\n\\tior\\n\\tistore %0\\n
   aload_0\\n\\tgetfield %J0/memory [I\\n\\t%0\\n\\tdup2\\n\\tiload %1\\n\\tbipush 8\\n\\tishr\\n\\tsipush 255\\n\\tiand\\n\\tiastore\\n\\ticonst_1\\n\\tiadd\\n\\tiload %1\\n\\tsipush 255\\n\\tiand\\n\\tiastore\\n
   aload_0\\n\\tgetfield %J0/memory [I\\n\\t%0\\n\\tdup2\\n\\t%K1\\n\\tbipush 8\\n\\tishr\\n\\tsipush 255\\n\\tiand\\n\\tiastore\\n\\ticonst_1\\n\\tiadd\\n\\t%K1\\n\\tsipush 255\\n\\tiand\\n\\tiastore\\n"
  [])

; This is the byte move, the simplest of them all.
;  - tw

(define_insn "movqi"
  [(set
    (match_operand:QI 0 "general_operand"  "=r,r,r,m,m")
    (match_operand:QI 1 "general_operand"    "r,i,m,r,i"))]
  ""
  "@
   iload %1\\n\\tistore %0\\n
   %K1\\n\\tistore %0\\n
   aload_0\\n\\tgetfield %J0/memory [I\\n\\t%1\\n\\tiaload\\n\\tistore %0\\n
   aload_0\\n\\tgetfield %J0/memory [I\\n\\t%0\\n\\tiload %1\\n\\tsipush 255\\n\\tiand\\n\\tiastore\\n
   aload_0\\n\\tgetfield %J0/memory [I\\n\\t%0\\n\\t%K1\\n\\tsipush 255\\n\\tiand\\n\\tiastore\\n"
  [])


;
; Extension and truncation insns.
; Those for integer source operand
; are ordered widest source type first.

;;(define_insn "extendsidi2"
;;  [(set (match_operand:DI 0 "register_operand" "=r")
;;        (sign_extend:DI (match_operand:SI 1 "general_operand" "g")))]
;;  ""
;;  "move.d %R1,%M0\;bpl 0f\;clear.d %H0\;moveq -1,%H0\\n0:")

;;(define_insn "extendhidi2"
;;  [(set (match_operand:DI 0 "register_operand" "=r")
;;        (sign_extend:DI (match_operand:HI 1 "general_operand" "g")))]
;;  ""
;;  "movs.w %R1,%M0\;bpl 0f\;clear.d %H0\;moveq -1,%H0\\n0:")

; Sign extend a half word to a word, easy.
;  - tw
(define_insn "extendhisi2"
  [(set (match_operand:SI 0 "register_operand" "=r,r")
        (sign_extend:SI (match_operand:HI 1 "general_operand" "r,i")))]
  ""
  "@
   iload %1\\n\\tbipush 16\\n\\tishl\\n\\tbipush 16\\n\\tishr\\n\\tistore %0\\n
   %K1\\n\\tbipush 16\\n\\tishl\\n\\tbipush 16\\n\\tishr\\n\\tistore %0\\n"
  [])

;;(define_insn "extendqidi2"
;;  [(set (match_operand:DI 0 "register_operand" "=r")
;;        (sign_extend:DI (match_operand:QI 1 "general_operand" "g")))]
;;  ""
;;  "movs.b %R1,%M0\;bpl 0f\;clear.d %H0\;moveq -1,%H0\\n0:")


; sign extend a byte to a word
;  - tw
(define_insn "extendqisi2"
  [(set (match_operand:SI 0 "register_operand" "=r,r")
        (sign_extend:SI (match_operand:QI 1 "general_operand" "r,i")))]
  ""
  "@
   iload %1\\n\\tbipush 24\\n\\tishl\\n\\tbipush 24\\n\\tishr\\n\\tistore %0\\n
   %K1\\n\\tbipush 24\\n\\tishl\\n\\tbipush 24\\n\\tishr\\n\\tistore %0\\n"
  [])

; sign extend a byte to a half word
;  - tw
(define_insn "extendqihi2"
  [(set (match_operand:HI 0 "register_operand" "=r,r")
        (sign_extend:HI (match_operand:QI 1 "general_operand" "r,i")))]
  ""
  "@
   iload %1\\n\\tbipush 8\\n\\tishl\\n\\tbipush 8\\n\\tishr\\n\\tistore %0\\n
   %K1\\n\\tbipush 8\\n\\tishl\\n\\tbipush 8\\n\\tishr\\n\\tistore %0\\n"
  [])

;
; Truncate.
;

; zero extend a half word to a word
;  - tw
(define_insn "zero_extendhisi2"
  [(set (match_operand:SI 0 "register_operand" "=r,r")
        (zero_extend:SI (match_operand:HI 1 "general_operand" "r,i")))]
  ""
  "@
   iload %1\\n\\tldc 65536\\n\\tiand\\n\\tistore %0\\n
   %K1\\n\\tldc 65536\\n\\tiand\\n\\tistore %0\\n"
  [])


; zero extend a byte to a word
;  - tw
(define_insn "zero_extendqisi2"
  [(set (match_operand:SI 0 "register_operand" "=r,r")
        (zero_extend:SI (match_operand:QI 1 "general_operand" "r,i")))]
  ""
  "@
   iload %1\\n\\tsipush 255\\n\\tiand\\n\\tistore %0\\n
   %K1\\n\\tsipush 255\\n\\tiand\\n\\tistore %0\\n"
  [])


; zero extend a byte to a half word
;  - tw
(define_insn "zero_extendqihi2"
  [(set (match_operand:HI 0 "register_operand" "=r,r")
        (zero_extend:HI (match_operand:QI 1 "general_operand" "r,i")))]
  ""
  "@
   iload %1\\n\\tsipush 255\\n\\tiand\\n\\tistore %0\\n
   %K1\\n\\tsipush 255\\n\\tiand\\n\\tistore %0\\n"
  [])


;
;
; Normal add operations.
;
; This is where we start to see the real load/store nature of the machine
;  - tw
(define_insn "addsi3"
  [(set (match_operand:SI 0 "general_operand" "=r,r,r,r")
        (plus:SI                           
         (match_operand:SI 1 "general_operand" "r,r,i,i")
         (match_operand:SI 2 "general_operand"  "r,i,r,i")))]
 ""                                         
 "@
  iload %1\\n\\tiload %2\\n\\tiadd\\n\\tistore %0\\n
  iload %1\\n\\t%K2\\n\\tiadd\\n\\tistore %0\\n
  %K1\\n\\tiload %2\\n\\tiadd\\n\\tistore %0\\n
  %K1\\n\\t%K2\\n\\tiadd\\n\\tistore %0\\n"
 [])

;;(define_insn "addhi3"
;;  [(set (match_operand:HI 0 "register_operand"         "=r,r,r,r,r,r")
;;        (plus:HI (match_operand:HI 1 "register_operand" "%0,0,0,0,0,r")
;;                 (match_operand:HI 2 "general_operand" "r,Q>,J,N,g,!To")))]
;;                                        ; Inhibit reloading to "To" alternative
;;  "" ; maybe we should sign/zero_extend the operand instead?
;;  "@ 
;;   add.w %2,%0
;;   add.w %2,%0
;;   addq %2,%0
;;   subq %n2,%0
;;   add.w %R2,%0
;;   add.w %R2,%1,%0"
;;  [])

;
;
; Normal mod operations.
;
(define_insn "modsi3"
  [(set (match_operand:SI 0 "general_operand" "=r,r,r,r")
        (mod:SI                           
         (match_operand:SI 1 "general_operand" "r,r,i,i")
         (match_operand:SI 2 "general_operand"  "r,i,r,i")))]
 ""                                         
 "@
  iload %1\\n\\tiload %2\\n\\tirem\\n\\tistore %0\\n
  iload %1\\n\\t%K2\\n\\tirem\\n\\tistore %0\\n
  %K1\\n\\tiload %2\\n\\tirem\\n\\tistore %0\\n
  %K1\\n\\t%K2\\n\\tirem\\n\\tistore %0\\n"
 [])

;;(define_insn "modhi3"
;;  [(set (match_operand:HI 0 "register_operand"         "=r,r,r,r,r,r")
;;        (mod:HI (match_operand:HI 1 "register_operand" "%0,0,0,0,0,r")
;;                 (match_operand:HI 2 "general_operand" "r,Q>,J,N,g,!To")))]
;;                                        ; Inhibit reloading to "To" alternative
;;  "" ; maybe we should sign/zero_extend the operand instead?
;;  "@ 
;;   rem.w %2,%0
;;   rem.w %2,%0
;;   remq %2,%0
;;   remq %n2,%0
;;   rem.w %R2,%0
;;   rem.w %R2,%1,%0"
;;  [])

;;(define_insn "umodhi3"
;;  [(set (match_operand:HI 0 "register_operand"         "=r,r,r,r,r,r")
;;        (umod:HI (match_operand:HI 1 "register_operand" "%0,0,0,0,0,r")
;;                 (match_operand:HI 2 "general_operand" "r,Q>,J,N,g,!To")))]
;;                                        ; Inhibit reloading to "To" alternative
;;  "" ; maybe we should sign/zero_extend the operand instead?
;;  "@ 
;;   rem.w %2,%0
;;   rem.w %2,%0
;;   remq %2,%0
;;   remq %n2,%0
;;   rem.w %R2,%0
;;   rem.w %R2,%1,%0"
;;  [])

;(define_insn "umodsi3"
;  [(set (match_operand:SI 0 "register_operand"         "=r,r,r,r")
;        (umod:SI (match_operand:SI 1 "register_operand" "r,r,i,i")
;                 (match_operand:SI 2 "general_operand" "r,i,r,i")))]
;  "" 
;  "@
;   iload %1\\n\\tiload %2\\n\\tirem\\n\\tistore %0\\n
;   iload %1\\n\\t%K2\\n\\tirem\\n\\tistore %0\\n
;   %K1\\n\\tiload %2\\n\\tirem\\n\\tistore %0\\n
;   %K1\\n\\t%K2\\n\\tirem\\n\\tistore %0\\n"
;  [])


;
; Subtract.
;

(define_insn "subsi3"
  [(set (match_operand:SI 0 "general_operand" "=r,r,r,r")
        (minus:SI                           
         (match_operand:SI 1 "general_operand" "r,r,i,i")
         (match_operand:SI 2 "general_operand"  "r,i,r,i")))]
 ""                                         
 "@
  iload %1\\n\\tiload %2\\n\\tisub\\n\\tistore %0\\n
  iload %1\\n\\t%K2\\n\\tisub\\n\\tistore %0\\n
  %K1\\n\\tiload %2\\n\\tisub\\n\\tistore %0\\n
  %K1\\n\\t%K2\\n\\tisub\\n\\tistore %0\\n"
 [])


;
;- Multiply instructions.
;
(define_insn "mulsi3"
  [(set (match_operand:SI 0 "general_operand" "=r,r,r,r")
        (mult:SI                           
         (match_operand:SI 1 "general_operand" "r,r,i,i")
         (match_operand:SI 2 "general_operand"  "r,i,r,i")))]
 ""                                         
 "@
  iload %1\\n\\tiload %2\\n\\timul\\n\\tistore %0\\n
  iload %1\\n\\t%K2\\n\\timul\\n\\tistore %0\\n
  %K1\\n\\tiload %2\\n\\timul\\n\\tistore %0\\n
  %K1\\n\\t%K2\\n\\timul\\n\\tistore %0\\n"
 [])

(define_insn "divsi3"
  [(set (match_operand:SI 0 "general_operand" "=r,r,r,r")
        (div:SI                           
         (match_operand:SI 1 "general_operand" "r,r,i,i")
         (match_operand:SI 2 "general_operand"  "r,i,r,i")))]
 ""                                         
 "@
  iload %1\\n\\tiload %2\\n\\tidiv\\n\\tistore %0\\n
  iload %1\\n\\t%K2\\n\\tidiv\\n\\tistore %0\\n
  %K1\\n\\tiload %2\\n\\tidiv\\n\\tistore %0\\n
  %K1\\n\\t%K2\\n\\tidiv\\n\\tistore %0\\n"
 [])



;
; Bitwise or.
;

(define_insn "iorsi3"
  [(set (match_operand:SI 0 "register_operand" "=r,r,r,r")
        (ior:SI (match_operand:SI 1 "register_operand" "r,r,i,i")
                (match_operand:SI 2 "register_operand" "r,i,r,i")))]
  ""
  "@
   iload %1\\n\\tiload %2\\n\\tior\\n\\tistore %0\\n
   iload %1\\n\\t%K2\\n\\tior\\n\\tistore %0\\n
   %K1\\n\\tiload %2\\n\\tior\\n\\tistore %0\\n
   %K1\\n\\t%K2\\n\\tior\\n\\tistore %0\\n"
  [])

(define_insn "andsi3"
  [(set (match_operand:SI 0 "register_operand" "=r,r,r,r")
        (and:SI (match_operand:SI 1 "register_operand" "r,r,i,i")
                (match_operand:SI 2 "register_operand" "r,i,r,i")))]
  ""
  "@
   iload %1\\n\\tiload %2\\n\\tiand\\n\\tistore %0\\n
   iload %1\\n\\t%K2\\n\\tiand\\n\\tistore %0\\n
   %K1\\n\\tiload %2\\n\\tiand\\n\\tistore %0\\n
   %K1\\n\\t%K2\\n\\tiand\\n\\tistore %0\\n"
  [])


;
;- xor instructions.
;

; See comment about "anddi3" for xordi3

(define_insn "xorsi3"
  [(set (match_operand:SI 0 "register_operand" "=r,r,r,r")
        (xor:SI (match_operand:SI 1 "register_operand" "r,r,i,i")
                (match_operand:SI 2 "register_operand" "r,i,r,i")))]
  ""
  "@
   iload %1\\n\\tiload %2\\n\\tixor\\n\\tistore %0\\n
   iload %1\\n\\t%K2\\n\\tixor\\n\\tistore %0\\n
   %K1\\n\\tiload %2\\n\\tixor\\n\\tistore %0\\n
   %K1\\n\\t%K2\\n\\tixor\\n\\tistore %0\\n"
  [])


;
; Negate insns.
;

;;(define_insn "negsi2"
;;  [(set (match_operand:SI 0 "register_operand" "=r")
;;        (neg:SI (match_operand:SI 1 "register_operand" "r")))]
;;  ""
;;  "neg.d %1,%0"
;;  [])


;
; One-complements
;

; See comment on anddi3

;;(define_insn "one_cmplsi2"
;;  [(set (match_operand:SI 0 "register_operand" "=r")
;;        (not:SI (match_operand:SI 1 "register_operand" "0")))]
;;  ""
;;  "not %0"
;;  [])


;
; Arithmetic shift right
;

(define_insn "ashrsi3"
  [(set (match_operand:SI 0 "register_operand" "=r,r,r,r")
        (ashiftrt:SI (match_operand:SI 1 "register_operand" "r,r,i,i")
                     (match_operand:SI 2 "general_operand" "r,i,r,i")))]
  ""
  "@
   iload %1\\n\\tiload %2\\n\\tishr\\n\\tistore %0\\n
   iload %1\\n\\t%K2\\n\\tishr\\n\\tistore %0\\n
   %K1\\n\\tiload %2\\n\\tishr\\n\\tistore %0\\n
   %K1\\n\\t%K2\\n\\tishr\\n\\tistore %0\\n"
  [])


;
; Logical shift right
;
; Ho hum, the bytecode below is long and gross because, once again, we
; don't have unsigned bytecodes. - tw
(define_insn "lshrsi3"
  [(set (match_operand:SI 0 "register_operand" "=r,r,r,r")
        (lshiftrt:SI (match_operand:SI 1 "register_operand" "r,r,i,i")
                     (match_operand:SI 2 "general_operand" "r,i,r,i")))]
  ""
  "@
   iload %1\\n\\tiload %2\\n\\tishr\\n\\ticonst_1\\n\\tiload %2\\n\\tishl\\n\\ticonst_1\\n\\tisub\\n\\tiand\\n\\tistore %0\\n
   iload %1\\n\\t%K2\\n\\tishr\\n\\ticonst_1\\n\\t%K2\\n\\tishl\\n\\ticonst_1\\n\\tisub\\n\\tiand\\n\\tistore %0\\n
   %K1\\n\\tiload %2\\n\\tishr\\n\\ticonst_1\\n\\tiload %2\\n\\tishl\\n\\ticonst_1\\n\\tisub\\n\\tiand\\n\\tistore %0\\n
   %K1\\n\\t%K2\\n\\tishr\\n\\ticonst_1\\n\\t%K2\\n\\tishl\\n\\ticonst_1\\n\\tisub\\n\\tiand\\n\\tistore %0\\n"
  [])


;
; Arithmetic/logical shift left
;

(define_insn "ashlsi3"
  [(set (match_operand:SI 0 "register_operand" "=r,r,r,r")
        (ashift:SI (match_operand:SI 1 "general_operand" "r,r,i,i")
                   (match_operand:SI 2 "general_operand" "r,i,r,i")))]
  ""
  "@
   iload %1\\n\\tiload %2\\n\\tishl\\n\\tistore %0\\n
   iload %1\\n\\t%K2\\n\\tishl\\n\\tistore %0\\n
   %K1\\n\\tiload %2\\n\\tishl\\n\\tistore %0\\n
   %K1\\n\\t%K2\\n\\tishl\\n\\tistore %0\\n"
  [])


;
; Various strange insns that gcc likes
;
;
; Note: abs only works in si (dword) mode, so we cannot define abshi2
; or absqi2.

;
; Fortunately, it is simple to construct an abssf
;
;;(define_insn "abssf2"
;;  [(set (match_operand:SF 0 "register_operand" "=r")
;;        (abs:SF (match_operand:SF 1 "register_operand" "0")))]
;;  ""
;;  "lslq 1,%0\;lsrq 1,%0")

;;(define_insn "abssi2"
;;  [(set (match_operand:SI 0 "register_operand" "=r")
;;        (abs:SI (match_operand:SI 1 "register_operand" "r")))]
;;  ""
;;  "abs %1,%0"
;;  [])

;;(define_expand "abshi2"
;;  [(set (match_dup 2)
;;        (sign_extend:SI (match_operand:HI 1 "general_operand" "g")))
;;   (set (match_dup 3) (abs:SI (match_dup 2)))
;;   (set (match_operand:HI 0 "register_operand" "=r")
;;        (subreg:HI (match_dup 3) 0))]
;;  "" ; maybe we should sign/zero_extend the operand instead?
;;  "operands[2] = gen_reg_rtx(SImode); operands[3] = gen_reg_rtx(SImode);")

;;(define_expand "absqi2"
;;  [(set (match_dup 2)
;;        (sign_extend:SI (match_operand:QI 1 "general_operand" "g")))
;;   (set (match_dup 3) (abs:SI (match_dup 2)))
;;   (set (match_operand:QI 0 "register_operand" "=r")
;;        (subreg:QI (match_dup 3) 0))]
;;  "" ; maybe we should sign/zero_extend the operand instead?
;;  "operands[2] = gen_reg_rtx(SImode); operands[3] = gen_reg_rtx(SImode);")

;
; Bound-insn.  Arithmetically defined to be the same as an unsigned
; minimum, which is an operation supported by gcc.  Used in casesi.
;
; May be useful too in insn combination; therefore the generalized pattern.
;

;;(define_insn "uminsi3"
;;  [(set (match_operand:SI 0 "general_operand" "=r,r,r,r")
;;        (umin:SI (match_operand:SI 1 "general_operand" "r,r,i,i")
;;                 (match_operand:SI 2 "general_operand" "r,i,r,i")))]
;;  ""
;;  "umin %1 %2 -> %0"
;;  [])

;;(define_insn "uminsi3"
;;  [(set (match_operand:SI 0 "register_operand"           "=r,r,r,r")
;;        (umin:SI  (match_operand:SI 1 "register_operand" "%0,0,0,r")
;;                  (match_operand:SI 2 "nonmemory_operand" "r,Q>,g,!To")))]
;;                                        ; Inhibit reloading to "To" alternative
;;  ""
;;  "*
;;{
;;  if (GET_CODE(operands[2]) == CONST_INT) {
;;    if (INTVAL(operands[2]) < 256)
;;      return \"bound.b %2,%0\";
;;    if (INTVAL(operands[2]) < 65536)
;;      return \"bound.w %2,%0\";
;;    return \"bound.d %2,%0\";
;;  } else if (which_alternative == 3)
;;      return \"bound.d %2,%1,%0\";
;;    else
;;      return \"bound.d %2,%0\";
;;}"
;; [])

;
; Jump and branch insns.
;
(define_insn "jump"
  [(set (pc)
        (label_ref (match_operand 0 "" "")))]
  ""
  "goto %l0"
  [])

;
; It seems we have to pretend a move from r15 to pc in order to
; convince gcc that a jump is done. (and match ordinary arithmetic insns)
;  There used to be a tm.h macro "PC_REGNUM", but that isnt used by
; gcc any more (v2.1).  We have to tell gcc explicitly when we jump.
; Pity.  Remove such dummy jumps with this insn.
;  Another use for this is to put out the "use" marks, so the
; jump-table or the default code wont be removed as dead code.
;  The default-case mark is used to output that label last in the
; table using ASM_OUTPUT_CASE_END.  If you change the order of the
; insns in define_expand casesi, you have to change ASM_OUTPUT_CASE_END too. 
;
(define_insn "dummy_jump"
  [(set (pc) (reg:SI 15))
   (use (label_ref (match_operand:SI 0 "" "")))
   (use (label_ref (match_operand:SI 1 "" "")))]
  ""
  "")

;
; It seems more appropriate to tell gcc that "r15 comes from pc" than
; to make gcc confused by the seemingly out-of-the-air use of r15.
;
(define_insn "dummy_jump2"
  [(set (reg:SI 15) (pc))]
  ""
  "")

; note that this doesn't have a chance in hell of working on the JVM
;  - tw
(define_insn "indirect_jump"
  [(set (pc) (match_operand:SI 0 "general_operand" "g"))]
  ""
  "jump %R0")

;
; Return insn - use whenever the epilogue is very simple;
;  if it is only a single ret or jump [sp+] (no saved registers or allocated
; stack space)
;  In this pattern, although named, it is legal to check for the
; context in the test, not only on compiler switches.
;
;
;;(define_insn "return"
;;  [(return)]
;;  "simple_epilogue()"
;;  "*
;;{
;;  int i;
;;
;;  /* Must be able to return a pointer to this */
;;  static char rd[80];
;;
;;  *rd = 0;
;;
;;  for (i = 8; i >= 0; i--)
;;    if (regs_ever_live[i])
;;       break;
;;  if (i >= 0) 
;;    sprintf(rd,\"movem [sp+],r%d\",i);
;;
;;  if (regs_ever_live[SRP_REGNUM]) {
;;    if (*rd)
;;      output_asm_insn(rd,operands);
;;    return \"jump [sp+]\";
;;  }
;;  if (*rd) {
;;    output_asm_insn(\"reT\",operands);
;;    return rd;
;;  }
;;  return \"ret%#\";
;;}"
;;  []) 

;
; Conditional branches.
;
; These are the unpaired branch instructions.  They really shouldn't show 
; up in your output unless you have a compare placed before a basic block.
; They load the "flags" field that is assumed to have been set by a
; compare instruction earlier. Unsigned members of this set DO NOT WORK.
;  - tw

(define_insn "beq"
  [(set (pc)
        (if_then_else (eq (cc0)
                          (const_int 0))
                      (label_ref (match_operand 0 "" ""))
                      (pc)))]
  ""
  "iload 15\\n\\tifeq %l0\\n"
  [])

(define_insn "bne"
  [(set (pc)
        (if_then_else (ne (cc0)
                          (const_int 0))
                      (label_ref (match_operand 0 "" ""))
                      (pc)))]
  ""
  "iload 15\\n\\tifne %l0\\n"
  [])

(define_insn "bgt"
  [(set (pc)
        (if_then_else (gt (cc0)
                          (const_int 0))
                      (label_ref (match_operand 0 "" ""))
                      (pc)))]
  ""
  "iload 15\\n\\tifgt %l0\\n"
  [])

(define_insn "bgtu"
  [(set (pc)
        (if_then_else (gtu (cc0)
                           (const_int 0))
                      (label_ref (match_operand 0 "" ""))
                      (pc)))]
  ""
  "iload 15\\n\\tifgt %l0 ; unsigned\\n"
  [])

(define_insn "blt"
  [(set (pc)
        (if_then_else (lt (cc0)
                          (const_int 0))
                      (label_ref (match_operand 0 "" ""))
                      (pc)))]
  ""
  "iload 15\\n\\tiflt %l0\\n"
  [])

(define_insn "bltu"
  [(set (pc)
        (if_then_else (ltu (cc0)
                           (const_int 0))
                      (label_ref (match_operand 0 "" ""))
                      (pc)))]
  ""
  "iload 15\\n\\tiflt %l0 ; unsigned\\n"
  [])

(define_insn "bge"
  [(set (pc)
        (if_then_else (ge (cc0)
                          (const_int 0))
                      (label_ref (match_operand 0 "" ""))
                      (pc)))]
  ""
  "iload 15\\n\\tifge %l0\\n"
  [])

(define_insn "bgeu"
  [(set (pc)
        (if_then_else (geu (cc0)
                           (const_int 0))
                      (label_ref (match_operand 0 "" ""))
                      (pc)))]
  ""
  "iload 15\\n\\tifge %l0\\n"
  [])

(define_insn "ble"
  [(set (pc)
        (if_then_else (le (cc0)
                          (const_int 0))
                      (label_ref (match_operand 0 "" ""))
                      (pc)))]
  ""
  "iload 15\\n\\tifle %l0\\n"
  [])

(define_insn "bleu"
  [(set (pc)
        (if_then_else (leu (cc0)
                           (const_int 0))
                      (label_ref (match_operand 0 "" ""))
                      (pc)))]
  ""
  "iload 15\\n\\tifle %l0 ; unsigned\\n"
  [])

;
; Reversed anonymous patterns to the ones above.
;

(define_insn ""
  [(set (pc)
        (if_then_else (eq (cc0)
                          (const_int 0))
                      (pc)
                      (label_ref (match_operand 0 "" ""))))]
  ""
  "bne %l0%#"
  [])

(define_insn ""
  [(set (pc)
        (if_then_else (ne (cc0)
                          (const_int 0))
                      (pc)
                      (label_ref (match_operand 0 "" ""))))]
  ""
  "beq %l0%#"
  [])

(define_insn ""
  [(set (pc)
        (if_then_else (gt (cc0)
                          (const_int 0))
                      (pc)
                      (label_ref (match_operand 0 "" ""))))]
  ""
  "*{ return (cc_prev_status.flags & CC_NO_OVERFLOW)
             ?  0 : \"ble %l0%#\";}"
  [])

;;(define_insn ""
;;  [(set (pc)
;;        (if_then_else (gtu (cc0)
;;                           (const_int 0))
;;                      (pc)
;;                      (label_ref (match_operand 0 "" ""))))]
;;  ""
;;  "bls %l0%#"
;;  [])

(define_insn ""
  [(set (pc)
        (if_then_else (lt (cc0)
                          (const_int 0))
                      (pc)
                      (label_ref (match_operand 0 "" ""))))]
  ""
  "*{ return (cc_prev_status.flags & CC_NO_OVERFLOW)
             ?  \"bpl %l0%#\" : \"bge %l0%#\";}"
  [])

;;(define_insn ""
;;  [(set (pc)
;;        (if_then_else (ltu (cc0)
;;                           (const_int 0))
;;                      (pc)
;;                      (label_ref (match_operand 0 "" ""))))]
;;  ""
;;  "bhs %l0%#"
;;  [])

(define_insn ""
  [(set (pc)
        (if_then_else (ge (cc0)
                          (const_int 0))
                      (pc)
                      (label_ref (match_operand 0 "" ""))))]
  ""
  "*{ return (cc_prev_status.flags & CC_NO_OVERFLOW)
             ?  \"bmi %l0%#\" : \"blt %l0%#\";}"
  [])

;;(define_insn ""
;;  [(set (pc)
;;        (if_then_else (geu (cc0)
;;                           (const_int 0))
;;                      (pc)
;;                      (label_ref (match_operand 0 "" ""))))]
;;  ""
;;  "blo %l0%#"
;;  [])

(define_insn ""
  [(set (pc)
        (if_then_else (le (cc0)
                          (const_int 0))
                      (pc)
                      (label_ref (match_operand 0 "" ""))))]
  ""
  "*{ return (cc_prev_status.flags & CC_NO_OVERFLOW)
             ?  0 : \"bgt %l0%#\";}"
  [])

;;(define_insn ""
;;  [(set (pc)
;;        (if_then_else (leu (cc0)
;;                           (const_int 0))
;;                      (pc)
;;                      (label_ref (match_operand 0 "" ""))))]
;;  ""
;;  "bhi %l0%#"
;;  [])

;
; SET on condition : Scc
;

;;(define_insn "sgeu"
;;  [(set (match_operand:SI 0 "register_operand" "=r")
;;        (geu (cc0) (const_int 0)))]
;;  ""
;;  "shs %0"
;;  [])

;;(define_insn "sltu"
;;  [(set (match_operand:SI 0 "register_operand" "=r")
;;        (ltu (cc0) (const_int 0)))]
;;  ""
;;  "slo %0"
;;  [])

;;(define_insn "seq"
;;  [(set (match_operand:SI 0 "register_operand" "=r")
;;        (eq (cc0) (const_int 0)))]
;;  ""
;;  "seq %0"
;;  [])

;;(define_insn "sge"
;;  [(set (match_operand:SI 0 "register_operand" "=r")
;;        (ge (cc0) (const_int 0)))]
;;  ""
;;  "*{ return (cc_prev_status.flags & CC_NO_OVERFLOW)
;;             ?  \"spl %0\" : \"sge %0\";}"
;;  [])

;;(define_insn "sgt"
;;  [(set (match_operand:SI 0 "register_operand" "=r")
;;        (gt (cc0) (const_int 0)))]
;;  ""
;;  "*{ return (cc_prev_status.flags & CC_NO_OVERFLOW)
;;             ?  0 : \"sgt %0\";}"
;;  [])

;;(define_insn "sgtu"
;;  [(set (match_operand:SI 0 "register_operand" "=r")
;;        (gtu (cc0) (const_int 0)))]
;;  ""
;;  "shi %0"
;;  [])

;;(define_insn "sle"
;;  [(set (match_operand:SI 0 "register_operand" "=r")
;;        (le (cc0) (const_int 0)))]
;;  ""
;;  "*{ return (cc_prev_status.flags & CC_NO_OVERFLOW)
;;             ?  0 : \"sle %0\";}"
;;  [])

;;(define_insn "sleu"
;;  [(set (match_operand:SI 0 "register_operand" "=r")
;;        (leu (cc0) (const_int 0)))]
;;  ""
;;  "sls %0"
;;  [])

;;(define_insn "slt"
;;  [(set (match_operand:SI 0 "register_operand" "=r")
;;        (lt (cc0) (const_int 0)))]
;;  ""
;;  "*{ return (cc_prev_status.flags & CC_NO_OVERFLOW)
;;             ?  \"smi %0\" : \"slt %0\";}"
;;  [])

;;(define_insn "sne"
;;  [(set (match_operand:SI 0 "register_operand" "=r")
;;        (ne (cc0) (const_int 0)))]
;;  ""
;;  "sne %0"
;;  [])

;
; CALL insns
;
;
; We need to make these patterns "expand", since the real operand is
; hidden in a (mem:QI ) inside operand[0] (call_value: operand[1]),
; and cannot be checked if it were a "normal" pattern.
;  I believe someone goofed when it comes to this mem-kind hiding,
; since it totally stops validation of operands on machines where the
; call-insn does NOT "automatically" strip the (mem) from its operands.
;  Note that "call" and "call_value" are ALWAYS called with a
; mem-operand for operand 0 and 1 respective.  What happens in cse and
; instruction combination is another issue.
;
(define_expand "call"
  [(parallel [(call (match_operand:QI 0 "memory_operand" "")
                    (match_operand:SI 1 "general_operand" ""))
              (clobber (reg:SI 16))])] 
  ""
  "")

;
; Accept ANYTHING as operand 1.  Accept operands for operand 0 in
; order of preference (Q includes r, but r is shorter, faster)
;
; The call instruction on the JVM is pretty cool.  I have decided to pass
; parameters in registers - well, this is what GCC thinks.  In fact we 
; fake it.  We get GCC to put the paramaters into registers 9 through 12
; (max four params at the moment) and then push them onto the stack to do
; the call.  The 'J' flag to print_operand prints the class name.
;  - tw
;
(define_insn ""
  [(call (mem:QI (match_operand:SI 0 "general_operand" "g"))
         (match_operand:SI 1 "general_operand" "i"))
   (clobber (reg:SI 16))] ;; 16 is the srp (can't use symbolic name)
  "" 
  "* 
   static char s[1024];	
   static char s1[40];	
   int highest=-1,i;
     /* just kill the call to __main */
     if (!strcmp(XEXP(operands[0],0),\"__main\")) return \"\";
     /* Find the highest used register */
     if (CALL_INSN_FUNCTION_USAGE (insn))
     {
       rtx link,theuse,thereg;

       for (link = CALL_INSN_FUNCTION_USAGE (insn); link != 0;
           link = XEXP (link, 1)) {
         theuse = XEXP(link,0);
         if (GET_CODE(theuse)!=USE) continue;
         thereg = XEXP(theuse,0);
         if (GET_CODE(thereg)!=REG) continue;
         if (REGNO(thereg)>highest) highest=REGNO(thereg);
       }  
     }
     strcpy(s,\"aload_0\\n\\t\");
     for (i=10; i<=highest; i++) {
       sprintf(s1,\"iload %i\\n\\t\", i);
       strcat(s,s1);
     }
     strcat(s,\"invokevirtual %J0/%0(\");
     for (i=10; i<=highest; i++)
       strcat(s,\"I\");
     strcat(s,\")\");
     strcat(s,\"V\\n\");
     return s;
  ")

(define_expand "call_value"
  [(parallel [(set (match_operand 0 "" "")
                   (call (match_operand:QI 1 "memory_operand" "")
                         (match_operand:SI 2 "general_operand" "")))
              (clobber (reg:SI 16))])] ;; 16 is the srp (can't use
  ""
  "")

;
; Accept ANYTHING as operand 2.  The validity other than "general" of
; operand 0 will be checked elsewhere.  Accept operands for operand 1 in
; order of preference (Q includes r, but r is shorter, faster)
;
(define_insn ""
  [(set (match_operand 0 "general_operand" "=g")
        (call (mem:QI (match_operand:SI 1 "general_operand" "g"))
              (match_operand:SI 2 "general_operand" "i")))
   (clobber (reg:SI 16))]
  ""
  "* 
   static char s[1024];
   static char s1[40];
   int highest=-1,i;
     /* Find the highest used register */
     if (CALL_INSN_FUNCTION_USAGE (insn))
     {  
       rtx link,theuse,thereg;
     
       for (link = CALL_INSN_FUNCTION_USAGE (insn); link != 0;
           link = XEXP (link, 1)) {
         theuse = XEXP(link,0);
         if (GET_CODE(theuse)!=USE) continue;
         thereg = XEXP(theuse,0);
         if (GET_CODE(thereg)!=REG) continue;
         if (REGNO(thereg)>highest) highest=REGNO(thereg);
       }  
     }
     strcpy(s,\"aload_0\\n\\t\");
     for (i=10; i<=highest; i++) {
       sprintf(s1,\"iload %i\\n\\t\", i);
       strcat(s,s1);
     }
     strcat(s,\"invokevirtual %J0/%1(\");
     for (i=10; i<=highest; i++)
       strcat(s,\"I\");
     strcat(s,\")\");
     strcat(s,\"I\\n\\tistore %0\\n\");
     return s;
  ")

;
; Used in debugging.  No usage for the direct pattern; unfilled
; delayed-branches are taken care of in other ways.
;
(define_insn "nop"
  [(const_int 0)]
  ""
  "")

;( define_insn "tablejump"
;  [(set (pc) (match_operand:SI 0 "general_operand" "g"))
;   (use (label_ref (match_operand 1 "" "")))]
;  ""
;  "Jump %0")

;
; No, let's use casesi instead. Will save a few cycles.
; Change back if "bound" insn is removed.
;
; NOTE: if you change the "parallell" (or add anything after it) in
; this expansion, you must change the macro ASM_OUTPUT_CASE_END
; accordingly, to add the default case at the end of the jump-table.
;
;;(define_expand "casesi"
;;  [(set (match_dup 5) (match_operand:SI 0 "general_operand" ""))
;;   (set (match_dup 6)
;;        (minus:SI (match_dup 5)
;;                  (match_operand:SI 1 "const_int_operand" "n")))
;;   (set (match_dup 7)
;;        (umin:SI (match_dup 6)
;;                 (match_operand:SI 2 "const_int_operand" "n")))
;;   (set (reg:SI 15) (pc))
;;   (set (reg:SI 15)
;;        (plus:SI (sign_extend:SI (mem:HI
;;                                  (plus:SI (mult:SI (match_dup 7)
;;                                                    (const_int 2))
;;                                           (reg:SI 15))))
;;                 (reg:SI 15)))
;;   (parallel
;;    [(set (pc) (reg:SI 15))
;;     (use (label_ref (match_operand 3 "" "")))
;;     (use (label_ref (match_operand 4 "" "")))])]
;;  ""
;;  "{ operands[2] = plus_constant(operands[2],1);
;;     operands[5] = gen_reg_rtx(SImode);
;;     operands[6] = gen_reg_rtx(SImode);
;;     operands[7] = gen_reg_rtx(SImode); }")


;;- Local variables:
;;- mode:emacs-lisp
;;- comment-start: ";;- "
;;- eval: (set-syntax-table (copy-sequence (syntax-table)))
;;- eval: (modify-syntax-entry ?[ "(]")
;;- eval: (modify-syntax-entry ?] ")[")
;;- eval: (modify-syntax-entry ?{ "(}")
;;- eval: (modify-syntax-entry ?} "){")
;;- End:
