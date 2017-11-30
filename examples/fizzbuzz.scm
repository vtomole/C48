(define (main-rec i limit) (cond ((= i limit) #t) ((= (remainder i 3) 0) (begin (print "Fizz") (main-rec (+ i 1) limit))) ((= (remainder i 5) 0) (begin (print "Buzz") (main-rec (+ i 1) limit))) ((or (= (remainder i 3) 0) (= (remainder i 3) 0))  (begin (print "FizzBuzz") (main-rec (+ i 1) limit))) (else (begin (print i) (main-rec (+ i 1) limit)))))
(define (main) (main-rec 0 100))
(main)