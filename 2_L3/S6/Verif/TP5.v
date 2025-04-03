(*TP 5*)
Require Import Arith.
Require Import Lia.
Require Export List.
Open Scope list_scope.
Import ListNotations.
Require Export List.
Import ListNotations.

Print list_ind.
Print app.

(*Exo 1*)
Inductive is_perm : list nat -> list nat -> Prop :=
  | is_perm_refl : forall l: list nat, is_perm l l
  | is_perm_avar : forall e: nat, forall l1 l2 : list nat, is_perm l1 l2 -> is_perm (e::l1) (l2++[e])
  | is_perm_sym : forall l1 l2: list nat, is_perm l1 l2 -> is_perm l2 l1
  | is_perm_trans : forall l1 l2 l3: list nat, is_perm l1 l2 -> is_perm l2 l3 -> is_perm l1 l3
  | is_perm_cons : forall e : nat, forall l1 l2 : list nat , is_perm l1 l2 -> is_perm (e::l1) (e::l2).

Goal is_perm [1;2;3] [3;2;1].
Proof.
apply (is_perm_avar 1 [2;3] [3;2]).
apply (is_perm_avar 2 [3] [3]).
apply is_perm_refl.
Qed.

Inductive is_sorted : list nat -> Prop :=
| is_sorted_nil : is_sorted nil
| is_sorted_un : forall e: nat, is_sorted (e::nil)
| is_sorted_cons : forall e h : nat, forall t: list nat, e <= h -> is_sorted (h::t) -> is_sorted (e::(h::t)).

Goal is_sorted [1;2;3].
Proof.
apply (is_sorted_cons 1 2 [3]).
+ lia.
+ apply (is_sorted_cons 2 3 []).
lia.
apply (is_sorted_un 3).
Qed.

(*Exo 2*)

Check le_dec.
Print sumbool.

Definition le_10 (n : nat) : bool :=
match (le_dec n 10) with
| left _ => true
| right _ => false
end.

Fixpoint insert (x : nat) (l : list nat) {struct l}: list nat :=
match l with
  |[] => [x]
  |e::q => match le_dec x e with
    | left _ => x::e::q
    | right _ => e::(insert x q)
  end
end.

Eval compute in (insert 3 [1;2;4;5]).

Fixpoint isort (l : list nat) : list nat:=
match l with
| nil => nil
|e::q => insert e (isort q)
end.

Eval compute in isort [9;8;7;6;5;4;3;2;1].


(*Exo 3*)
Lemma head_is_perm : forall (x1 x2 : nat) (l : list nat), is_perm (x1 :: x2 :: l) (x2 :: x1 :: l).
Proof.
intros.
apply( is_perm_trans (x1:: x2 :: l) ((x2:: l) ++ [x1])).
+ simpl.
apply (is_perm_avar x1 (x2:: l) (x2::l)).
apply (is_perm_refl).
+ apply (is_perm_sym).
simpl.
apply is_perm_sym.
apply (is_perm_trans ((x2 ::l) ++[x1]) ((x2::l)++[x1])).
++ simpl.
apply is_perm_refl.
++simpl.
apply (is_perm_cons x2 (l ++ [x1]) (x1::l)).
apply is_perm_sym.
apply (is_perm_avar x1 (l) (l)).
apply is_perm_refl.
Qed.


Lemma insert_is_perm : forall (x : nat) (l : list nat), is_perm (x::l) (insert x l).
Proof.
induction l.
+ simpl.
apply is_perm_refl.
+ simpl.
elim (le_dec x a).
++ intro.
apply is_perm_refl.
++ intro.
apply is_perm_sym.
apply (is_perm_trans (a::insert x l) ( a::x::l)).
+++ apply (is_perm_cons a (insert x l) (x::l)).
apply is_perm_sym.
apply IHl.
+++ apply (is_perm_trans (a::x::l) ((x::l)++[a])).
++++ apply (is_perm_avar a (x::l) (x::l)).
apply is_perm_refl.
++++ apply is_perm_sym.
simpl.
apply(is_perm_cons x (a :: l) (l ++ [a]) ).
apply(is_perm_avar a l l).
apply is_perm_refl.
Qed.

Lemma insert_is_sorted : forall (x : nat) (l : list nat), is_sorted l -> is_sorted (insert x l).
Proof.
intros.
elim H.
+ simpl.
apply is_sorted_un.
+intros.
simpl.
elim (le_dec x e).
++intros.
apply (is_sorted_cons).
apply a.
apply( is_sorted_un).
++ intros.
apply (is_sorted_cons).
lia.
apply (is_sorted_un).
+ simpl.
intro.
intro.
elim (le_dec).
++ intros.
elim(le_dec).
intro.
apply is_sorted_cons.
lia.
apply is_sorted_cons.
lia.
apply H1.
intro.
apply is_sorted_cons.
lia.
apply H2.
++ intros.
elim le_dec.
intros.
apply is_sorted_cons.
apply a.
apply is_sorted_cons.
apply H0.
apply H1.
intros.
apply is_sorted_cons.
apply H0.
apply H2.
Qed.


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
apply is_sorted_nil.
intros.
rewrite H.
simpl.
elim (IHl (isort l)).
intros.
split.
apply is_perm_trans with (a :: (isort l)).
apply is_perm_cons.
apply H0.
apply insert_is_perm.
apply insert_is_sorted.
assumption.
reflexivity.
Qed.
















