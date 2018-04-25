(define (nthcdr n l)
  (if (= n 0) l (nthcdr (- n 1) (cdr l))))

(define (nth n list)
       (car (nthcdr n list)))
