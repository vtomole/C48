(define (floop start stop fn)
      (cond
        ((> start stop) (quote ()))
        ((= start stop) (list(fn start)))
        (else (cons (fn start) (floop (+ start 1) stop fn))) 
       )
     )



