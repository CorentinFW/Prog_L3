(*TD 1*)
(*Exo 1 *)
Parameter A B C : Prop.

Goal A -> B -> A.
Proof.
intros.
assumption.
Qed.

Goal (A -> B -> C) -> (A -> B) -> A -> C.
Proof.
intros.
apply H.
assumption.
apply H0.
assumption.
Qed.

Goal A /\ B ->B.
Proof.
intros.
elim H.
intros.
assumption.
Qed.

Goal B -> A \/ B.
Proof.
intro.
right.
assumption.
Qed.

Goal (A \/ B) -> (A -> C) -> (B -> C) -> C.
Proof.
intro.
intro.
intro.
destruct H.
apply H0.
assumption.
apply H1.
assumption.
Qed.

Goal A -> False -> ~A.
Proof.
intros.
intro.
apply H0.
Qed.

Goal False -> A.
Proof.
intros.
elim H.
Qed.

Goal (A <-> B) -> A -> B.
Proof.
intros.
elim H.
intros.
apply H1.
assumption.
Qed.

Goal (A <-> B) -> B -> A.
Proof.
intros.
elim H.
intros.
apply H2.
assumption.
Qed.

Goal (A->B)->(B->A)->(A<->B).
Proof.
intros.
split.
assumption.
assumption.
Qed.


(*Exo 2*)
Parameter E: Set.
Parameter P Q : E -> Prop.

Goal forall x : E, P(x) -> exists y : E,P(y) \/ Q(y).
Proof.
intros.
exists x.
left.
assumption.
Qed.

Goal (exists x: E,P(x) \/ Q(x)) -> (exists x :E,P(x)) \/ (exists x :E,Q(x)).
Proof.
intros.
destruct H.
elim H.
intro.
left.
exists x.
assumption.
intro.
right.
exists x.
assumption.
Qed.

Goal (forall x:E, P(x)) /\ (forall x:E, Q(x)) -> forall x:E, P(x) /\ Q(x).
Proof.
intro.
destruct H.
intro.
split.
apply H.
apply H0.
Qed.

Goal (forall x:E, P(x) /\ Q(x)) -> (forall x:E,P(x)) /\ (forall x:E,Q(x)).
Proof.
intro.
split.
apply H.
apply H.
Qed.

Goal (forall x:E,~P(x)) -> ~(exists x:E, P(x)).
Proof.
intro.
intro.
elim H0.
apply H.
Qed.


(*exo 4*)
Parameter R : E->E->Prop.
Goal (exists x:E,forall y:E,R(x)(y)) -> forall y:E,exists x:E,R(x)(y).
Proof.
intro.
intro.
destruct H.
exists x.
apply H.
Qed.


Goal (forall x:E,forall y:E,R(x)(y)) -> forall x:E,forall y:E,R(y)(x).
Proof.
intro.
intro.
intro.
apply H.
Qed.

Goal (exists x:E,exists y:E,R(x)(y)) -> exists y:E,exists x:E,R(x)(y).
Proof.
intro.
elim H.
intro.
intro.
elim H0.
intros.
exists x0.
exists x.
assumption.
Qed.

(*(le 4 est un copier coller du 1 donc skip)*)

Goal forall x:E,(forall y:E,P(y) -> P(x)) -> (exists y:E,P(y)) -> P(x).
Proof.
intro.
intro.
intro.
elim H0.
apply H.
Qed.

Require Import Classical.
Parameters a b c: E.
Goal exists x:E,P(x) -> P(a) /\ P(b).
Proof.
apply NNPP.
intro.
elimtype False.
apply H.
exists a.
intro.
split.
assumption.
elimtype False.
apply H.
exists b.
intro.
split.
assumption.
assumption.
Qed.

Goal exists x:E,P(x) -> P(a) /\ P(b)/\P(c).
Proof.
apply NNPP.
intro.
elimtype False.
apply H.
exists a.
intro.
split.
assumption.
elimtype False.
apply H.
exists b.
intro.
split.
assumption.
split.
assumption.
elimtype False.
apply H.
exists c.
intro.
split.
assumption.
split.
assumption.
assumption.
Qed.

Goal exists x:E,P(x) -> forall y:E,P(y).
Proof.
apply NNPP.
intro.
elimtype False.
apply H.
exists a.
intro.
intro.
apply NNPP.
intro.
apply H.
exists y.
intro.
elimtype False.
apply H1.
assumption.
Qed.


Goal (exists x:E,Q(a) -> P(x)) -> Q(a) -> exists x:E,P(x).
Proof.
intros.
destruct H.
exists x.
apply H.
assumption.
Qed.

Goal (Q(a) -> exists x:E,P(x)) -> exists x:E,Q(a) -> P(x).
intros.
apply NNPP.
intro.
apply H0.
exists a.
intro.
destruct H.
assumption.
elimtype False.
apply H0.
exists x.
intro.
assumption.
Qed.


(*TP 2 *)
(* EXO 3 *)

Open Scope type_scope.
Section Iso_axioms.
Variables A B C : Set.
Axiom Com : A * B = B * A.
Axiom Ass : A * (B * C) = A * B * C.
Axiom Cur : (A * B -> C) = (A -> B -> C).
Axiom Dis : (A -> B * C) = (A -> B) * (A -> C).
Axiom P_unit : A * unit = A.
Axiom AR_unit : (A -> unit) = unit.
Axiom AL_unit : (unit -> A) = A.
End Iso_axioms.



Lemma isos_ex1 : forall A B :Set, A * (B -> unit) = A.
Proof.
intro.
intro.
rewrite Com.
rewrite AR_unit.
rewrite Com.
rewrite P_unit.
reflexivity.
Qed.

Lemma isos_ex2 : forall A B : Set, A * unit * B = B * (unit * A).
Proof.
intros.
rewrite P_unit.
rewrite (Com unit A0).
rewrite Ass.
rewrite P_unit.
rewrite Com.
reflexivity.
Qed.



Lemma isos_ex3 : forall A B C : Set,
(A * unit -> B * (C * unit)) =
(A * unit -> (C -> unit) * C) * (unit -> A -> B).
Proof.
intros.
rewrite AR_unit.
rewrite AL_unit.
rewrite P_unit.
rewrite P_unit.
rewrite (Com unit C0).
rewrite P_unit.
rewrite Dis.
rewrite Com.
reflexivity.
Qed.


Ltac ALL :=
  intros;
  repeat rewrite AR_unit;
  repeat rewrite AL_unit;
  repeat rewrite P_unit;
  repeat rewrite Ass;
  repeat rewrite Cur;
  repeat rewrite Dis;
  try rewrite Com;
  try reflexivity.

Lemma isos_ex1B : forall A B :Set, A * (B -> unit) = A.
Proof.
ALL.
Qed.



(*Exo 4*)


Section Peano.
Parameter N : Set.
Parameter o : N.
Parameter s : N -> N.
Parameters plus mult : N -> N -> N.
Variables x y : N.
Axiom ax1 : ~((s x) = o).
Axiom ax2 : exists z, ~(x = o) -> (s z) = x.
Axiom ax3 : (s x) = (s y) -> x = y.
Axiom ax4 : (plus x o) = x.
Axiom ax5 : (plus x (s y)) = s (plus x y).
Axiom ax6 : (mult x o) = o.
Axiom ax7 : (mult x (s y)) = (plus (mult x y) x).
End Peano.


Goal plus (s o) (s (s o)) = s( s (s o )).
Proof.
rewrite ax5.
rewrite ax5.
rewrite ax4.
reflexivity.
Qed.

Goal plus (s (s o ) ) (s ( s o ) ) = s ( s (s (s o ) ) ).
Proof.
rewrite ax5.
rewrite ax5.
rewrite ax4.
reflexivity.
Qed.

Goal mult (s ( s o) ) (s ( s o )) = s ( s (s (s o ) ) ).
Proof.
rewrite ax7.
rewrite ax7.
rewrite ax6.
rewrite ax5.
rewrite ax5.
rewrite ax4.
rewrite ax5.
rewrite ax5.
rewrite ax4.
reflexivity.
Qed.


Ltac Peano_tac := 
  repeat(
    try rewrite ax1;
    try rewrite ax2;
    try rewrite ax3;
    try rewrite ax4;
    try rewrite ax5;
    try rewrite ax6;
    try rewrite ax7;
    try reflexivity
  ).


Lemma UnPlusDeuxEgalTrois2 : (plus (s o) (s (s o))) = (s (s (s o))).

Proof.
  Peano_tac.
Qed.

Lemma DeuxPlusDeuxEgalQuatre2 : (plus (s (s o)) (s (s o))) = (s (s (s (s o)))).

Proof.
  Peano_tac.
Qed.

Lemma DeuxFoisDeuxEgalQuatre2 : (mult (s (s o)) (s (s o))) = (s (s (s (s o)))).

Proof.
  Peano_tac.
Qed.



Hint Rewrite ax2 ax3 : negatif.
Hint Rewrite ax7 ax6 : mults.
Hint Rewrite ax5 ax4 : adds.

Goal (plus (s o) (s (s o))) = (s (s (s o))).
Proof.
autorewrite with adds using try reflexivity.
Qed.

Goal (plus (s (s o)) (s (s o))) = (s (s (s (s o)))).
Proof.
autorewrite with adds using try reflexivity.
Qed.

Goal (mult (s (s o)) (s (s o))) = (s (s (s (s o)))).
Proof.
autorewrite with mults using try reflexivity.
autorewrite with adds using try reflexivity.
Qed.









