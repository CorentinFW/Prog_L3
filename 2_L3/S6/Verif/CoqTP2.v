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

















