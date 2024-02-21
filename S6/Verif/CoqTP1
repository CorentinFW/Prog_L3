(*Exo 1*)
(*1*)
Parameters A B : Prop.
Goal A -> B -> A.
intro.
intro.
assumption.
Qed.
(*2*)
Parameter C : Prop.
Goal (A -> B-> C) -> (A -> B) -> A-> C.
intros.
apply H.
assumption.
apply H0.
assumption.
Qed.
(*3*)
Goal A /\ B -> B.
intros.
elim H.
intros.
assumption.
Qed.
(*4*)
Goal B -> A \/ B.
intros.
right.
assumption.
Qed.
(*5*)
Goal (A \/ B) -> (A -> C) -> (B -> C) -> C.
intros.
elim H.
intro.
apply H0.
assumption.
assumption.
Qed.

(*6*)
Goal A -> False -> ~A.
intros.
intro.
assumption.
Qed.

(*7*)
Goal False -> A.
intros.
elimtype False.
assumption.
Qed.

(*8*)
Goal (A <-> B) -> A -> B.
intros.
elim H.
intros.
apply H1.
assumption.
Qed.

(*9*)
Goal (A <-> B) -> B -> A.
intros.
elim H.
intros.
apply H2.
assumption.
Qed.

(*10*)
Goal (A -> B) -> (B -> A) -> (A <-> B).
intros.
split.
assumption.
assumption.
Qed.
(*EXO 2 *)
Parameter E : Set.
Parameter P : E -> Prop.
Parameter Q : E -> Prop.
Goal forall x : E,(P x) -> (exists y : E,(P y) \/ (Q y)).
intros.
exists x.
left.
assumption.
Qed.

(*2*)
Goal (exists x : E,(P x) \/ (Q x)) -> (exists x : E,(P x))\/ (exists x : E,(Q x)).
intros.
left.
elim H.
elim H.
intros.
exists x.
elim H0.
intro.
assumption.
intro.
elim H.
intro.
intro.
elim H3.











