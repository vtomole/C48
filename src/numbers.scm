(* 4 5)

(+ 137 349)

(- 1000 334)

(* 5 99)

(/ 576 45)

(+ 21 56 48 97)

(- 1 2)

(/ 68 5 4 2)

(* 1 2 3 5 6)

(+ (* 3 5) (- 10 6))

(+ -1 -2)

(+ (* 3
(+ (* 2 4)
(+ 3 5)))
(+ (- 10 7)
6))

(
define pi 3)
(define radius 10)
(* pi (* radius radius))

(* (+ 2 (* 4 6))
(+ 3 5 7))

(define (square x) (* x x))
(square 21)
(square (+ 2 5))
(square (square 3))

(define (sum-of-squares x y)
(+ (square x) (square y)))
(sum-of-squares 3 4)

(define (f a)
(sum-of-squares(+ a 1) (* a 2)))
(f 5)

(define (abs x)
(cond ((> x 0) x)
((= x 0) 0)
((< x 0) (- 0 x))))

(abs 5)
(abs -5)

(define (a-plus-abs-b a b)
((if (> b 0) + -) a b))
(a-plus-abs-b 4 -5)


