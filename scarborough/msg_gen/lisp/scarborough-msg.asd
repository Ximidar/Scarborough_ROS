
(cl:in-package :asdf)

(defsystem "scarborough-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils )
  :components ((:file "_package")
    (:file "YPR" :depends-on ("_package_YPR"))
    (:file "_package_YPR" :depends-on ("_package"))
    (:file "Motor_Speed" :depends-on ("_package_Motor_Speed"))
    (:file "_package_Motor_Speed" :depends-on ("_package"))
  ))