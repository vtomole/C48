(define (for-loop start stop fn)
      (cond
        ((> start stop) (quote ()))
        ((= start stop) (list(fn start)))
        (else (cons (fn start) (for-loop (+ start 1) stop fn))) 
       )
      )

(define (fn a)
        (print (* a a)))

(for-loop 0 5 fn)
