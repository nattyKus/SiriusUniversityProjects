data Person = Person { firstName :: String, lastName :: String, age :: Int }

abbrFirstName :: Person -> Person
abbrFirstName p@(Person {firstName = (x:y:s)}) = p {firstName = x:"."}
abbrFirstName p = p