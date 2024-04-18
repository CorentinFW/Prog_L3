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