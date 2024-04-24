Require Import Arith.
Require Import Lia.
Require Export List.
Open Scope list_scope.
Import ListNotations.
Require Export Recdef.


(*Fixpoint c'est Definition pour recursion*)
(*EXO 1 *)

Inductive is_mem : nat -> list nat -> Prop :=
|is_mem_base : forall (e : nat) (l : list nat), is_mem e (e::l)
|is_mem_cons : forall (e h : nat) (li : list nat), is_mem e li -> is_mem e (h::li).

Goal is_mem 3 [8;9;7;2;1;3].
apply is_mem_cons.
apply is_mem_cons.
apply is_mem_cons.
apply is_mem_cons.
apply is_mem_cons.
apply is_mem_base.



Fixpoint mem (n : nat) (l : list nat) : bool :=
match l with
|[] => false
|h::t => match Nat.eq_dec h n with
  |left _ => true
  |_ => mem n t
  end
end.


Eval compute in mem 1 [8;9;7;2;1;3].
Qed.

Lemma mem_is_mem : forall (x : nat) (l : list nat), mem (x) (l) = true -> is_mem (x) (l).
intro.
intro.
elim l.
simpl.
intro.
inversion H. (*quand y a une hypothese fausse*)
simpl.
intro.
elim Nat.eq_dec.
intros.
rewrite a0.
apply is_mem_base.
intros.
apply is_mem_cons.
apply H.
apply H0.
Qed.




Lemma comp_is_mem : forall (x : nat) (l : list nat), is_mem (x) (l) -> mem (x) (l) = true.
intros.
elim H.
intro.
simpl.
elim Nat.eq_dec.
intro.
reflexivity.
intros.
elim l0.
simpl.
auto.
intros.
elim l0.
simpl.
elim Nat.eq_dec.
intro.
reflexivity.
intros.
apply H0.
intros.
apply H1.
intros.
simpl.
elim Nat.eq_dec.
intros.
reflexivity.
intros.
apply H1.
Qed.

(*Exo 3*)

(* 1 *)

Definition f_gcd (a b : nat * nat) :=
(fst a) + (snd a) < (fst b) + (snd b).

Function gcd (c : nat * nat) {wf f_gcd c} : option nat := (*wf = well founded , {wf ..} pour dire que la relation f_gcd est appliquer sur c*)
match c with
| (0, 0) => None
| (0, _) => None
| (_, 0) => None
| _ =>
let n := fst c in
let m := snd c in
match (lt_eq_lt_dec n m) with
| inleft a =>
match a with
| left _ => gcd (n, (m - n))
| right _ => Some n (*Some : on a bien calculer n*)
end
| inright a => gcd ((n - m), m)
end
end.
intros.
unfold f_gcd.
simpl.
lia.
intros.
unfold f_gcd. (* remplace un terme par sa definition formelle *)
simpl.
lia.
apply well_founded_ltof.
Defined.

Eval compute in gcd( 2 , 6).

(* 2*)
Definition divides (r : nat) (a : nat * nat) := r <> 0 -> (exists (b : nat), b*r = (fst a)) /\ (exists (b : nat), b*r = (snd a)).

(* 3 *)
Lemma gcd_divides : forall ( a b r : nat), a <> 0 -> b <> 0 -> r <> 0 -> gcd(a,b) = Some r -> divides r (a,b).
intro.
intro.
functional induction (gcd(a,b));intros.
inversion H2.
inversion H2.
inversion H2.
unfold divides.
intro.
split.







