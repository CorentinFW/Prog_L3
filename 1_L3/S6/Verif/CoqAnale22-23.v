Inductive bin : Set :=
| C0 : bin
| C1 : bin
| C0S : bin -> bin
| C1S : bin -> bin.


Eval compute in C0S (C1S C1).

(*1*)

Inductive is_even : bin -> Prop :=
|is_even_C0 : is_even C0
|is_even_C0S :forall a, is_even(C0S a).

Goal is_even (C0S (C1S C1)).
Proof.
apply is_even_C0S.
Qed.

(*2*)

Fixpoint head_0 (b : bin) : bin :=
match b with
|C0 => C0S (C0)
|C1 => C1S (C0)
|C1S a => C1S (head_0 (a))
|C0S a => C0S (head_0 (a))
end.

Compute head_0 (C0S (C1S C1)).

(*3*)
Inductive is_equal : bin -> bin -> Prop:=
|is_equal_sym : forall (a b : bin), is_equal (b)(a) -> is_equal (a)(b)
|is_equal_trans : forall (a b c : bin), is_equal(a)(b) -> is_equal(b)(c)
|is_equal_refl : forall (a : bin), is_equal (a)(a)
|is_equal_head : forall(a b : bin), is_equal (head_0 a)(b) -> is_equal (a)(b) .

Goal is_equal (C0S (C1S C1)) (C0S (C1S (C1S(C0S(C0))))).
apply is_equal_head.
apply is_equal_head.
simpl.
apply is_equal_refl.
Qed.

(*4*)

Definition mult_2 (b: bin) := C0S b.
Compute mult_2 (C0S (C1S C1)).

(*5*)

Goal forall b : bin, is_even(b) -> (exists a : bin, is_equal(b) (mult_2(a))).
intros.
induction b.

exists C0.
apply is_equal_head.
apply is_equal_refl.
easy.
exists b.
apply is_equal_refl.
easy.
Qed.


























