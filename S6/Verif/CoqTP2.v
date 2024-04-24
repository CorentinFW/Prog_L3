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

Lemma isos_ex1 : forall A B: Set, A* (B -> unit) = A.

Proof.
intros.
rewrite AR_unit.
rewrite P_unit.
reflexivity.
Qed.


Lemma isos_ex2 : forall A B :Set, A * unit * B = B * (unit * A).

Proof.
  intros.
  rewrite P_unit.
  rewrite <- (Com A unit).
  rewrite <- (Com B A).
  rewrite P_unit.
  reflexivity.
Qed.

Lemma isos_ex3 : forall A B C : Set,
(A * unit -> B * (C * unit)) =
(A * unit -> (C -> unit) * C) * (unit -> A -> B).

Proof.
  intros.
  rewrite AR_unit.
  rewrite P_unit.
  rewrite P_unit.
  rewrite AL_unit.
  rewrite Dis.
  rewrite Dis.
  rewrite AR_unit.
  rewrite (Com unit (A->C)).
  rewrite P_unit.
  rewrite Com.
  reflexivity.
Qed.


Ltac Norm_axioms :=
  repeat (
    try rewrite Com;
    try rewrite Ass;
    try rewrite Cur;
    try rewrite Dis;
    try rewrite P_unit;
    try rewrite AR_unit;
    try rewrite AL_unit;
    try reflexivity
  ).

Ltac tactNorm :=
  intros;
  Norm_axioms.


Lemma isos_ex12 : forall A B :Set, A * (B -> unit) = A.
Proof.
  tactNorm.
Qed.

Lemma isos_ex22 : forall A B :Set, A * unit * B = B * (unit * A).
Proof.
  tactNorm.
Qed.

(*Exo 4 : Peano*)

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

Lemma UnPlusDeuxEgalTrois : (plus (s o) (s (s o))) = (s (s (s o))).

Proof.
  rewrite ax5.
  rewrite ax5.
  rewrite ax4.
  reflexivity.
Qed.

Lemma DeuxPlusDeuxEgalQuatre : (plus (s (s o)) (s (s o))) = (s (s (s (s o)))).

Proof.
  rewrite ax5.
  rewrite ax5.
  rewrite ax4.
  reflexivity.
Qed.

Lemma DeuxFoisDeuxEgalQuatre : (mult (s (s o)) (s (s o))) = (s (s (s (s o)))).

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


Ltac Peano_tactique :=
  repeat (
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
  Peano_tactique.
Qed.

Lemma DeuxPlusDeuxEgalQuatre2 : (plus (s (s o)) (s (s o))) = (s (s (s (s o)))).

Proof.
  Peano_tactique.
Qed.

Lemma DeuxFoisDeuxEgalQuatre2 : (mult (s (s o)) (s (s o))) = (s (s (s (s o)))).

Proof.
  Peano_tactique.
Qed.






