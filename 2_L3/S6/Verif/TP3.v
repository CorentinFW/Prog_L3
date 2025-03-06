(*TP3*)
(*1*)
Definition Ttrue (A:Prop) (x y : A) := x.
Definition Ffalse (A:Prop) (x y : A) := y.
Definition ifthenelse (B:Prop) (b:forall (A:Prop), forall (x y : A),A) (u:B) (v:B) := b B u v.
Definition Bool forall (A : Prop),(x y : A), A.
Definition not (b : bool) := bool b bool Ffalse Ttrue.
