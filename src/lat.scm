(define lat
  (lambda (l)
    (cond
     ((null? l) #t)
     ((atom? (car l)) (lat (cdr l)))
     (else #f))))

(lat '( 1 2 2 ))
