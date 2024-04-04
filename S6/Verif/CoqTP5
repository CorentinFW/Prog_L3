Require Import Arith.
Require Import Lia.
Require Export List.
Open Scope list_scope.
Import ListNotations.

Parameter E : Type.

(*EXO 1 *)
Inductive is_perm : list nat -> list nat -> Prop :=
| is_perm_refl : forall l : list nat, is_perm l l
| is_perm_sym : forall l1 l2 : list nat, is_perm l1 l2 -> is_perm l2 l1
| is_perm_trans : forall l1 l2 l3 : list nat, is_perm l1 l2 -> is_perm l2 l3 -> is_perm l1 l3
| is_perm_cons : forall (e : nat) (l1 l2 : list nat), is_perm l1 l2 -> is_perm (e :: l1) (e :: l2)
| is_perm_append : forall (e : nat) (l : list nat),is_perm (e :: l) (l ++ e::nil).



Variables a b c : nat.
Goal is_perm [a; b; c] [c; b; a].
apply( is_perm_trans [a; b; c] ([b; c] ++ [a])).
apply is_perm_append.
simpl.
apply( is_perm_trans [b;c;a] ([c;a]++[b])).
apply is_perm_append.
simpl.
apply is_perm_cons.
apply( is_perm_trans [a;b] ([b]++[a])).
apply is_perm_append.
simpl.
apply is_perm_refl.
Qed.


Inductive is_sorted : list nat -> Prop :=
| est_trier_vide : is_sorted []
| est_trier_singleton : forall x : nat, is_sorted [x]
| est_trier_cons : forall (x y : nat) (l : list nat),
    x <= y -> is_sorted (y :: l) -> is_sorted (x :: y :: l).

Lemma exemple_est_trier : is_sorted [1; 2; 3; 4].
Proof.
  apply est_trier_cons. apply le_S. apply le_n.
  apply est_trier_cons. apply le_S. apply le_n.
  apply est_trier_cons. apply le_S. apply le_n.
  apply est_trier_singleton.
Qed.

(*EXO 2*)

(*1*)

Check le_dec.
Print sumbool.

Definition le_10 (n : nat) : bool :=
  match(le_dec n 10) with
  | left _ => true
  | right _ => false
end.


Eval compute in le_10 10.

(*2*)

Fixpoint insert (x : nat) (l : list nat) {struct l} : list nat :=
  match l with 
    | [] => [x]
    | e::q => match le_dec x e with 
      | left _ => x::e::q
      | right _ => e::(insert x q)
end
end.

(*3*)

Eval compute in insert 3 [1;2;4;5].

(*4*)

Fixpoint isort (l : list nat) : list nat :=
  match l with
  | nil => nil
  | e::q => insert e (isort q)
end.

(*5*) 

Eval compute in isort [9;8;7;6;5;4;3;2;1].

(*EXO 3*)

(*1*)

Lemma head_is_perm : forall (x1 x2 : nat) (l : list nat),
is_perm(x1::x2:: l)(x2::x1:: l).
Proof.
intros.
apply( is_perm_trans (x1:: x2 :: l) ((x2:: l) ++ [x1])).
apply is_perm_append.
simpl.
apply is_perm_cons.
apply is_perm_sym.
apply is_perm_append.
Qed.

(*2*)

Lemma insert_is_perm : forall (x : nat) (l : list nat),
is_perm (x::l) (insert x l).
induction l.
apply is_perm_sym.
simpl.
apply is_perm_refl.
simpl.
elim(le_dec x a0).
intros.
apply is_perm_refl.
intros.
apply(is_perm_trans (x :: a0 :: l) (a0 :: x :: l)).
apply head_is_perm.
apply is_perm_cons.
apply IHl.
Qed.

(*3*)
Lemma insert_is_sorted : forall (x : nat) (l : list nat),
is_sorted l -> is_sorted (insert x l).
intros.
elim H.
simpl.
apply est_trier_singleton.
intros.
simpl.
elim(le_dec x x0).
intros.
apply est_trier_cons.
apply a0.
apply est_trier_singleton.
intros.
apply est_trier_cons.
lia. (*solveur de preuve arithmetique*)
apply est_trier_singleton.
simpl.
intro.
intro.
elim(le_dec).
intros.
elim(le_dec).
intro.
apply est_trier_cons.
lia.
apply est_trier_cons.
lia.
apply H1.
intro.
apply est_trier_cons.
lia.
apply H2.
intros.
elim le_dec.
intros.
apply est_trier_cons.
lia.
apply est_trier_cons.
lia.
apply H1.
intros.
apply est_trier_cons.
lia.
apply H2.
Qed.

(*4*)
Lemma isort_correct : forall (l l' : list nat), (*induction sur la liste l*)
l' = isort l -> is_perm l l' /\ is_sorted l'.
induction l.
intros.
split.
rewrite H. (* rewrite quand y une égalité *)
simpl.
apply is_perm_refl.
rewrite H.
simpl.
apply est_trier_vide.
intros.
rewrite H.
simpl.
elim (IHl (isort l)).
intros.
split.
apply is_perm_trans with (a0 :: (isort l)).
apply is_perm_cons.
apply H0.
apply insert_is_perm.
apply insert_is_sorted.
assumption.
reflexivity.
Qed.

