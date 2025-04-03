(*TP4*)
(*Exo 2*)
Check forall A: Type, A -> (A -> A) -> A.
Check( fun n :(forall F: Type,F->(F->F)->F) => n (forall F: Type,F->(F->F)->F)).

Set Universe Polymorphism.
Definition my_nat := forall A: Type, A -> (A -> A) -> A.
Check fun n : my_nat=>n my_nat.

(*Exo 4*)
Print nat.
Check nat_rec.


Definition double : nat->nat:= fun n : nat => nat_rec (fun n : nat=>nat) 0 (fun p a : nat => S (S n)) n.


Definition pred : nat->nat := fun n : nat=> nat_rec (fun n : nat=>nat) 0 (fun r v :nat => r) n.
Check (pred 4).

Definition plus : nat->nat->nat := fun n m: nat=>nat_rec (fun n : nat=>nat) m (fun r v : nat=> S v) n.

(*EXO 4*)

(*1*)
Print nat.
Print nat.
Check nat_rec.

(*2*)
Compute (double 2).
Compute (pred 4).
Compute (plus 2 2).

(*3*)
Theorem inf_n_sn : forall n : nat, n <= S n.
Proof.
  exact(
  fun n => nat_ind (fun x => x <= S x) 
                    (le_S 0 0 (le_n 0))
                    (fun p => fun a =>  (le_S (S p) (S p) (le_n (S p))))
          n
).
Qed.
Theorem inf_n_sn_bis : forall n : nat, n <= S n.
  Proof.
  induction n.
  + apply (le_S 0 0).
  apply (le_n).
  + apply le_S.
  apply le_n.
Qed.

(*EXO5*)
Fixpoint mult (n m : nat ): nat := 
  match n with
  | 0 => 0
  | S p => plus (mult p m) m
end.

Compute mult 4 5.

Lemma P2 : forall n , mult 2 n = plus n n.
Proof.
intro.
simpl.
reflexivity.
Qed.

Lemma aux0 : forall n, (plus n 2) = S (S n).
Proof.
intro.
elim n.
+ simpl.
reflexivity.
+ intros.
simpl.
rewrite H.
reflexivity.
Qed.

Lemma aux1 : forall n m, (plus n (S m)) = S (plus n m).
Proof.
intros.
elim n.
+ simpl.
reflexivity.
+ intros.
simpl.
rewrite H.
reflexivity.
Qed.

Lemma P2_2 : forall n , mult n 2 = plus n n.
Proof.
intro.
elim n.
+ simpl.
reflexivity.
+ intro.
intro.
simpl.
rewrite (aux0 (mult n0 2)).
rewrite H.
rewrite (aux1 n0 n0).
reflexivity.
Qed.


(*EXO 6*)

Open Scope list.
Require Export List.
Import ListNotations.

Print list_ind.
Print app.

Parameter E : Type.
Fixpoint rev (l : list E) {struct l} : list E :=
  match l with
  | nil => nil
  | e::q => (rev q) ++(e::nil)
end.

Theorem q2 : forall l : list E, forall e : E, rev(l ++ (e::nil))= e::rev(l).
Proof.
intro.
intro.
elim l.
+ simpl.
reflexivity.
+ intros.
simpl.
rewrite H.
reflexivity.
Qed.


Theorem q3 : forall l :list E, rev (rev l) = l.
Proof.
intros.
elim l.
+ simpl.
reflexivity.
+ intros.
simpl.
rewrite q2.
rewrite H.
reflexivity.
Qed.







