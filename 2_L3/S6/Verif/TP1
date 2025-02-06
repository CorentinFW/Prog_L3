Parameters A B C : Prop.

(*EXO 1 *)
Print A.
Goal A -> B -> A.
Proof.
intro.
intro.
apply H.
Qed.

Goal (A->B->C)->(A->B)->A->C.
Proof.
intro.
intro.
intro.
apply H.
apply H1.
apply H0.
apply H1.
Qed.

Goal A/\ B-> B.
Proof.
intro.
destruct H.
apply H0.
Qed.

Goal B -> A \/ B.
Proof.
intro.
right.
apply H.
Qed.

Goal (A\/B)->(A->C)->(B->C) -> C.
Proof.
intros.
destruct H.
apply H0.
apply H.
apply H1.
apply H.
Qed.

Goal A -> False -> ~A.
Proof.
intros.
intro.
apply H0.
Qed.

Goal False -> A.
intro.
elim H.
Qed.


Goal (A<->B) -> A -> B.
Proof.
intro.
intro.
destruct H.
apply H.
apply H0.
Qed.

Goal (A<->B) -> B -> A.
Proof.
intros.
destruct H.
apply H1.
apply H0.
Qed.

Goal (A->B)->(B->A)->(A<->B).
Proof.
intros.
split.
apply H.
apply H0.
Qed.

(*Exo 2*)

Parameter E : Set.
Parameter P : E -> Prop.
Parameter Q : E -> Prop.

Goal forall x : E,P(x) -> exists y : E, P(y) \/Q(y).
Proof.
intro.
intro.
exists x.
left.
apply H.
Qed.


Goal (exists x :E,P(x) \/ Q(x)) -> (exists x : E,P(x)) \/ (exists x : E,Q(x)).
Proof.
intro.
elim H.
intro.
intro.
elim H0.
intro.
left.
exists x .
apply H1.
intro.
right.
exists x.
apply H1.
Qed.

(*3*)
Goal (forall x:E,P(x)) /\ (forall x:E,Q(x)) -> forall x:E,P(x)/\Q(x).
Proof.
intro.
intro.
split.
elim H.
intros.
apply H0.
elim H.
intros.
apply H1.
Qed.
(*4*)

Goal (forall x:E,P(x) /\ Q(x)) ->(forall x:E,P(x)) /\(forall x:E,Q(x)).
Proof.
intro.
split.
apply H.
apply H.
Qed.

(*5*)

Goal (forall x:E,~P(x)) -> ~(exists x:E,P(x)).
Proof.
intro.
intro.
elim H0.
apply H.
Qed.

(*6*)

Goal ~(forall x:E,P(x)) -> exists x:E,~P(x).
Proof.
Admitted.


(*Exo 4*)

Parameter R : E -> E-> Prop.
(*1*)
Goal (exists x :E,forall y:E,R(x)(y)) -> forall y:E,exists x:E,R(x)(y).
intro.
intro.
elim H.
intros.
exists x.
apply H0.
Qed.

(*2*)
Goal (forall x :E,forall y:E,R(x)(y)) -> forall x:E,forall y:E,R(y)(x).
Proof.
intro.
intro.
intro.
apply H.
Qed.

(*3*)
Goal (exists x :E,exists y:E,R(x)(y)) -> exists x:E,exists y:E,R(x)(y).
Proof.
intro.
elim H.
intros.
elim H0.
intros.
exists x.
exists x0.
apply H1.
Qed.

(*4. (∃x.∀y.R(x, y)) ⇒ ∀y.∃x.R(x, y) *)
Goal (exists x :E,forall y: E,R(x)(y)) -> forall y :E,exists x:E,R(x)(y).
Proof.
intro.
elim H.
intro.
intro.
intro.
exists x.
apply H0.
Qed.


(*5. ∀x.(∀y.P (y) ⇒ P (x)) ⇒ (∃y.P (y)) ⇒ P (x) *)
Goal forall x:E,(forall y:E,P(y) -> P(x)) -> (exists y :E,P(y)) -> P(x).
Proof.
intro.
intro.
intro.
elim H0.
apply H.
Qed.

Require Import Classical.

Parameters a b c: E.
(*6. ∃x.P (x) ⇒ P (a) ∧ P (b) *)
Goal exists x :E,P(x) -> P(a) /\ P(b).
Proof.
apply NNPP.
intro.

elimtype False.
apply H.
exists a.
intro.
split.
apply H0.
elimtype False.
apply H.
exists b.
intro.
split.
apply H0.
apply H1.
Qed.

(*7. ∃x.P (x) ⇒ P (a) ∧ P (b) ∧ P (c) *)
Goal exists x :E,P(x) -> P(a) /\ P(b) /\ P(c).
Proof.
apply NNPP.
intro.
elimtype False.
apply H.
exists a.
intro.
split.
apply H0.
elimtype False.
apply H.
exists b.
intro.
elimtype False.
apply H.
exists c.
intro.
split.
apply H0.
split.
apply H1.
apply H2.
Qed.

(*8. ∃x.P (x) ⇒ ∀y.P (y) *)

Goal exists x : E,P(x) -> forall y:E,P(y).
Proof.
apply NNPP.
intro.
cut (~ (exists x : E, P x -> forall y : E, P y)).
+
(*mtn c'est aled*)
intro.
apply H0.
exists a.
intro.
intro.
apply NNPP.
intro.
apply H.
exists y.
intro.
intro.
elimtype False.
apply H2.
apply H3.
+
assumption.
Qed.



(*9. (∃x.Q(a) ⇒ P (x)) ⇒ Q(a) ⇒ ∃x.P (x) *)
Goal (exists x:E,Q(a) -> P(x)) -> Q(a) ->  exists x:E,P(x).
intro.
intro.
elim H.
intro.
intro.
exists x.
apply H1.
apply H0.
Qed.

(*10. (Q(a) ⇒ ∃x.P (x)) ⇒ ∃x.Q(a) ⇒ P (x) *)
Goal (Q(a) -> exists x : E, P(x)) -> exists x:E,Q(a) -> P(x).
intro.
apply NNPP.
intro.
elimtype False.
apply H0.
exists a.
intro.
destruct H.
apply H1.
elimtype False.
apply H0.
exists x.
intro.
apply H.
Qed.




















