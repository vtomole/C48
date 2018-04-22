(define (factorial i) (if (= i 1) 1 (* i (factorial (- i 1)))))
(define (main) (let ((i 5)) (factorial i)))
(main)
