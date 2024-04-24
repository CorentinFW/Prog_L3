(*TP3 *)
Open Scope list.
Parameter E : Type.

(*EXO 1*)
Fixpoint plus (n m : nat) : nat :=
match n with 
| 0 => m
|S p => S(plus p m)
end.

Compute (plus 5 7).

Fixpoint mult (n m : nat) : nat :=
match n with
| 0 => 0
|S p => (plus (mult p m) m)
end.

Compute (mult 0 5).


Goal forall n : nat, mult 2 n = plus n n.
intro.
simpl.
reflexivity.
Qed.

Lemma aux0 : forall n, (plus n 2) = S( S n).
intros.
elim n.
simpl.
reflexivity.
intros.
simpl.
rewrite H.
reflexivity.
Qed.

Lemma aux1 : forall n m, (plus n (S m)) = S(plus n m).
intro.
elim n.
intro.
simpl.
reflexivity.
intros.
simpl.
rewrite H.
reflexivity.
Qed.

Goal forall n: nat,mult n 2 = plus n n.
intro.
elim n.
simpl.
reflexivity.
intros.
simpl.
rewrite H.
rewrite aux0.
rewrite aux1.
reflexivity.
Qed.

(*EXO 2*)
Fixpoint rev(l : list E) : list E :=
match l with
| nil => nil
| e::q => (rev q) ++ (e::nil)
end.

Lemma ex2_2 : forall l : list E, forall e : E,
rev(l ++ e::nil) = e::(rev l).
intros.
elim l.
simpl.
reflexivity.
intros.
simpl.
rewrite H.
reflexivity.
Qed.

Lemma ex2_3 : forall l : list E, rev(rev(l)) = l.
intros.
elim l.
simpl; reflexivity.
intros;simpl.
rewrite ex2_2.
rewrite H.
reflexivity.
Qed.

(*EXO 4*)
Inductive is_perm : list E -> list E -> Prop :=
| is_perm_refl : forall l : list E, is_perm l l
| is_perm_sym : forall l1 l2 : list E, is_perm l1 l2 -> is_perm l2 l1
| is_perm_trans : forall l1 l2 l3 : list E, is_perm l1 l2 -> is_perm l2 l3 -> is_perm l1 l3
| is_perm_cons : forall (e : E) (l1 l2 : list E), is_perm l1 l2 -> is_perm (e :: l1) (e :: l2)
| is_perm_append : forall (e : E) (l : list E),is_perm (e :: l) (l ++ e::nil).

Require Export List.
Import ListNotations.

Variables a b c : E.
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




