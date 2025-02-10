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
(*exo 3*)
Lemma isos_ex1 : forall A B :Set, A * (B -> unit) = A.
Proof.
intro.
intro.
rewrite AR_unit.
rewrite P_unit.
reflexivity.
Qed.


Lemma isos_ex2 : forall A B : Set, A * unit * B = B * (unit * A).
Proof.
intros.
rewrite P_unit.
rewrite (Com unit A).
rewrite (Ass B A unit).
rewrite P_unit.
rewrite Com.
reflexivity.
Qed.

Lemma isos_ex3 : forall A B C : Set,(A * unit -> B * (C * unit)) =(A * unit -> (C -> unit) * C) * (unit -> A -> B).
Proof.
intros.
rewrite AL_unit.
rewrite AR_unit.
rewrite P_unit.
rewrite P_unit.
rewrite Dis.
rewrite Dis.
rewrite AR_unit.
rewrite (Com unit (A->C)).
rewrite P_unit.
rewrite Com.
reflexivity.
Qed.


Lemma P_unit2 : forall A:Set,unit*A = A.
Proof.
intros.
rewrite (Com unit A).
rewrite P_unit.
reflexivity.
Qed.

Ltac ALL :=
  intros;
  repeat rewrite AR_unit;
  repeat rewrite AL_unit;
  repeat rewrite P_unit;
  repeat rewrite P_unit2;
  repeat rewrite Ass;
  repeat rewrite Cur;
  repeat rewrite Dis;
  try rewrite Com;
  try reflexivity.

Lemma isos_ex1Bis : forall A B :Set, A * (B -> unit) = A.
Proof.
ALL.
Qed.


Lemma isos_ex2Bis : forall A B : Set, A * unit * B = B * (unit * A).
Proof.
ALL.
Qed.


Lemma isos_ex3Bis : forall A B C : Set,(A * unit -> B * (C * unit)) =(A * unit -> (C -> unit) * C) * (unit -> A -> B).
Proof.
ALL.
Qed.


(*Exo4*)
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

Goal (plus(s o) (s (s o))) = (s (s (s o))).
Proof.
rewrite ax5.
rewrite ax5.
rewrite ax4.
reflexivity.
Qed.

Goal (plus (s (s o)) (s (s o))) = (s (s (s (s o ) ) ) ).
Proof.
rewrite ax5.
rewrite ax5.
rewrite ax4.
reflexivity.
Qed.

Goal (mult (s ( s o)) (s (s o))) = (s (s (s (s o )))).
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







