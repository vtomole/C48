(define (for-loop start stop fn)
      (cond
        ((> start stop) (quote ()))
        ((= start stop) (list(fn )))
        (else (cons (fn ) (for-loop (+ start 1) stop fn))) 
       )
      )



