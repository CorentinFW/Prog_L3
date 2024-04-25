(*Annales 2022 3 *)
Require Import Arith.
Require Import Lia.
Require Export List.
Open Scope list_scope.
Import ListNotations.
Require Export Recdef.


Parameter E : Set.
Parameter Q P : E -> Prop.
Parameter a : E.
(*Exo1*)
(*1*)
Goal (exists x: E, P(x)) /\ (forall x :E,P(x) -> Q(x)) -> exists x:E,Q(x).
Proof.
intros.
destruct H.
destruct H.
apply H0 in H.
exists x.
assumption.
Qed.

(*2*)
Goal (exists x:E, P(x) /\ Q(x)) ->(exists x:E, P(x) -> Q(x)).
Proof.
intros.
destruct H.
exists x.
destruct H.
intro.
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

Goal forall (a b : R), mult(plus(a)(b))(plus one one) = plus(b)(plus(a)(plus(b)(a))).
intros.
rewrite dis_left.
rewrite dis_right.




