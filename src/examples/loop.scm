(define (loop-rec i limit)
  (if (= i limit) #t
      (begin (print i)
	     (loop-rec (+ i 1)))))

(loop-rec 0 100)
