(*Annales 2022 2 *)
Require Import Arith.
Require Import Lia.
Require Export List.
Open Scope list_scope.
Import ListNotations.
Require Export Recdef.

Parameter E : Set.
Parameter Q P : E -> Prop.
Parameter a : E.

(*Exo 1 *)
(*1*)
Goal (forall x : E,P(x) -> Q(x)) /\ P(a) -> 
(exists x: E,Q(x)).
Proof.
intro.
destruct H.
apply H in H0.
exists a.
assumption.
Qed.

(*2*)
Goal (exists x: E, P(x) /\ Q(x)) -> 
(exists x: E,P(x)) \/(exists x: E,Q(x)).
intro.
destruct H.
left.
destruct H.
exists x.
assumption.
Qed.

(*Exo 2*)
Parameter R : Set .
Parameters zero one : R.
Parameter opp : R -> R.
Parameters plus mult : R -> R -> R.
Section Commutative_ring.
Variables a b c : R.
Axiom ass_plus : plus ( plus a b ) c = plus a ( plus b c ).
Axiom com_plus : plus a b = plus b a .
Axiom com_mult : mult a b = mult b a .
Axiom ass_mult : mult ( mult a b ) c = mult a ( mult b c ).
Axiom dis_left : mult a ( plus b c ) = plus ( mult a b ) ( mult a c ).
Axiom dis_right : mult ( plus b c ) a = plus ( mult b a ) ( mult c a ) .
Axiom neu_plus_r : plus a zero = a .
Axiom neu_plus_l : plus zero a = a .
Axiom neu_mult_r : mult a one = a .
Axiom neu_mult_l : mult one a = a .
Axiom opp_right : plus a ( opp a ) = zero .
Axiom opp_left : plus ( opp a ) a = zero .
End Commutative_ring .

Goal forall(a b: R),mult(plus one one)(plus(a)(b)) =
plus(a)(plus(b)(plus(a)(b))).
Proof.
intros.
rewrite dis_right.
rewrite neu_mult_l.
rewrite ass_plus.
reflexivity.
Qed.

(*Exo 3*)
Require Export List.
Open Scope list_scope.
Import ListNotations.

Inductive is_rev : list nat -> list nat -> Prop :=
| is_rev_nil : is_rev nil nil
| is_rev_cons : forall (n : nat) (l1 l2 : list nat),
  is_rev l1 l2 -> is_rev (n::l1) (l2 ++ [n]).

Fixpoint rev(l : list nat) {struct l} : list nat :=
match l with 
| nil => nil
| e::q => (rev q) ++ (e :: nil)
end.

Goal forall (l1 l2 : list nat), (is_rev l1 l2) -> (rev l1) = l2.
Proof.
intros.
elim H.
simpl.
reflexivity.
intros.
simpl.
rewrite H1.
reflexivity.
Qed.












