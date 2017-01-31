type sign = Neg | NonNeg and bigint = sign * int list (* IS A TUPLE *)
let rec convert_int_input_to_list_of_modten (x:int) :int list = 
	if (x>=0) then 
		if (x/10 < 1) then []@[x] else convert_int_input_to_list_of_modten(x mod 10)@convert_int_input_to_list_of_modten(x/10)

	else convert_int_input_to_list_of_modten(-1*x)

let get_sign (x:int) =
	if(x>=0) then NonNeg else Neg

let convert_Ocamlint2bigint (x:int) :bigint = 
	(get_sign(x),convert_int_input_to_list_of_modten(x))

let negate (x:bigint) = match x with 
|(Neg , y) -> (NonNeg , y)
|(NonNeg , y ) -> (Neg , y)

let absolute (x:bigint) = match x with 
|( y , list) -> (NonNeg , list)
let rec remove_e_z_from_list x = match List.rev x with |y::ys -> if(y=0) then remove_e_z_from_list(List.rev ys) else x |[]->[]

let rec compareVs v1 v2 = match (remove_e_z_from_list v1), (remove_e_z_from_list v2) with
| [], []-> 0
| ([0],[]|[],[0])->0
|[], _-> 2
| _, []-> 1
| x::xs, y::ys -> if (x = y) then (compareVs xs ys) else if (x>y) then 1 else 2

let is_same_sign (x:bigint) (y:bigint) = match x,y with
	|(Neg,_),(NonNeg,_)-> false
	|(NonNeg,_),(Neg,_) -> false
	|(_,_),(_,_) -> true
	(* is_same_sign (NonNeg,[2;1]) (Neg,[1;2;3]);; *)
let sign_of x = match x with 
	|(Neg , a) -> -1
	|(a,b) -> 1
let sign_of_k y = 
	if(sign_of(y)=(-1)) then Neg else NonNeg

let is_equal (x:bigint) (y:bigint) = 
	if(is_same_sign x y) then
	if(	match x with
		| (a,b) -> match y with | (c,d) -> (compareVs b d) ) =0 
	then true else false 
else false
	  
let is_greater x y = 
	if(sign_of(x)<sign_of(y))then false else
	if(	match x with
		| (a,b) -> match y with | (c,d) -> (compareVs b d)) = 1 then true else false

let is_lessthan x y = 
	if(sign_of(x)>sign_of(y))then false else
	if(
		match x with
		| (a,b) -> match y with | (c,d) -> (compareVs b d)) = 2 then true else false

let is_lessthan_equal_to x y = if((is_equal x y)||(is_lessthan x y)) then true else false
let is_greaterthan_or_equal_to x y = if((is_equal x y)||(is_greater x y)) then true else false

let rec sum_of_lists (x:int list) (y:int list) = 
	match x , y with 
	| [],[] -> [0]@[]
	| a::ax,[] -> [a]@(sum_of_lists ax [])
	| [],a::ax -> [a]@(sum_of_lists [] ax)
	| a::[],b::[]->if(a+b<10) then [(a+b)]@(sum_of_lists [] []) else [a+b-10]@[1]@(sum_of_lists [] [])
	| a::ax,b::by -> if(a+b<10) then [(a+b)]@(sum_of_lists ax by)else
	[10-a-b]@(sum_of_lists ax [((List.hd by)+1)]@(List.tl by))


let rec tens_compliment x = match List.rev x with 
	|a::[] -> [10-a] 
	|a::ax -> [9-a]@tens_compliment(ax) 


let rec diff_of_list_req (x:int list) (y:int list) :int list =  match x,y with 
	| [],[] -> [0]@[]
	| a::ax,[] -> [a]@(diff_of_list_req ax [])
	(* | [],a::ax -> [a]@(diff_of_list_req [] ax) *)
	| a::[],b::[]-> if (a-b>=0) then [(a-b)] @ (diff_of_list_req [] []) else [b-a]@(diff_of_list_req [] [])
	| a::ax,b::by -> if (a-b>=0) then [(a-b)] @ (diff_of_list_req ax by) else
	 [10+a-b] @ (diff_of_list_req([(List.hd ax)-1]@List.tl ax) by)

let subract_two_big_ints (x:bigint) (y:bigint): bigint = (* subtract y from x*)
	match x,y with |(a,b),(c,d) -> 
		if(is_lessthan x y) then (* handle an error here *)
			(sign_of_k(negate(y)),(diff_of_list_req d b))
				 else (sign_of_k(x),(diff_of_list_req b d)) 
 

 let add_two_big_ints (x:bigint) (y:bigint):bigint = (* subract_two_big_ints (NonNeg,[2;1;2]) (NonNeg,[5;1;5]);; i assume they are both of same sign if not then send to subract_two_big_ints *)
	if(sign_of(x)<>sign_of(y)) then (subract_two_big_ints x y) else
	match x,y with |(a,b),(c,d)->(a,(sum_of_lists b d)) 

let rec my_mult_by_const l1 m c=
if (List.length(l1)>1) then

[(((List.hd(l1))*m) + c)mod 10]@ my_mult_by_const (List.tl(l1)) m 
((((List.hd(l1))*m) + c)/10)

else [(((List.hd(l1))*m)+c)mod 10]@[(((List.hd(l1))*m)+c)/10]@[]

let rec my_mult l1 l2= if (List.length(l2)=1) then my_mult_by_const (l1) (List.hd(l2)) 0
else match l2 with |x::xs -> sum_of_lists (my_mult_by_const (l1) (x) (0)) (my_mult l1 xs)

let mult (x:bigint) (y:bigint) = match x,y with 
|(a,b),(c,d) -> if(sign_of(x)*sign_of(y)=1) then (NonNeg, my_mult (b) (d)) else (Neg,my_mult (b) (d))
exception NOT_VALID

let rec remove_e_z_from_bigint x = match x with |(a,b)-> (a,remove_e_z_from_list(b)) 
let rec quotient acc x y = match y with|(a,ax)->
if( is_equal y (NonNeg,[0;0]) ) then raise NOT_VALID
   else if (is_greaterthan_or_equal_to x y) then quotient (acc+1) (subract_two_big_ints (remove_e_z_from_bigint(x)) (remove_e_z_from_bigint(y))) y else  convert_Ocamlint2bigint(acc)
let divide x y = quotient 0 x y
let remainder x y =	 
	subract_two_big_ints x (quotient 0 x y);;

(* let rec fact acc x = match x with
	(NonNeg,[1]) -> acc
|	_ -> fact (remove_e_z_from_bigint (mult acc x)) (remove_e_z_from_bigint (subract_two_big_ints x (NonNeg,[1])))
;;

let a = fact (NonNeg,[1]) (NonNeg,[0;0;0;1]);;
let b = fact (NonNeg,[1]) (NonNeg,[0;0;5]);;
let c = divide a b;; GOD LEVEL CODE
 *)