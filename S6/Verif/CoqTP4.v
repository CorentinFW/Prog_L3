Inductive IsFact : nat -> nat -> Prop := 
| Is_Fact_0 : IsFact 0 1
| Is_Fact_S : forall n m : nat,
IsFact n m -> IsFact (S n) ((S n) * m).

Fixpoint fact(n : nat) : nat :=
match n with
|0 => 1
|S p => (S p) * fact p
end.

Lemma fact_correct_1 :
forall n m, fact(n) = m -> IsFact n m.
induction n.
intros.
rewrite <- H.
simpl.
apply Is_Fact_0.
intros.
rewrite <- H.
simpl.
apply Is_Fact_S.
apply IHn.
reflexivity.
Qed.

Lemma my_fact_ind : forall P : nat -> nat -> Prop,
    P 0 1 -> (forall n, P n (fact n) -> P (S n) (S n * fact n)) -> forall n, P n (fact n).
Proof.
induction n.
assumption.
apply H0.
assumption.
Qed.

Print my_fact_ind.

Require Import FunInd.
Functional Scheme fact_ind := Induction for fact Sort Prop.
Print fact_ind.

Lemma correct_fact_fun_ind1 :
forall n m, fact n = m -> IsFact n m.
Proof.
intro.
functional induction (fact n) using fact_ind.
intros x EQ.
rewrite <- EQ.
apply Is_Fact_0.
intros x EQ.
rewrite <- EQ.
apply Is_Fact_S.
apply IHn0.
reflexivity.
Qed.