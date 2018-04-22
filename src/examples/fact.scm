(define (factorial i) (if (= i 1) 1 (begin (define j (- i 1 ))
					   (* i (factorial j)))))
(define (main) (define i 5) (print (factorial i)))
(main)
