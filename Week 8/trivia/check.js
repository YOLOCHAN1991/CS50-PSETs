function MCcheck(event)
            {
                // using id's so it's harder to someone to find the answer checking the web inspector
                var correctanswer = document.querySelector('#a').id;
                var answerbutton = event.srcElement;
                if (answerbutton.id == correctanswer)
                {
                    answerbutton.style.backgroundColor = 'green';
                    answerbutton.style.color = "white";
                    document.querySelectorAll('.section hr')[0].innerHTML = "Correct";
                }
                else
                {
                    answerbutton.style.backgroundColor = "#ba0000";
                    answerbutton.style.color = "white";
                    document.querySelectorAll('.section hr')[0].innerHTML = "Incorrect";
                }
            }

            function FRcheck(event)
            {
                var submitbutton = event.target.querySelectorAll('input')[1];
                var answer = document.getElementById("answer001");
                let correctanswer = "Mount Everest".toLowerCase();
                if (answer.value.toLowerCase() == correctanswer)
                {
                    submitbutton.style.backgroundColor = 'green';
                    submitbutton.style.color = "white";
                    document.querySelectorAll('.section hr')[1].innerHTML = "Correct";
                }
                else
                {
                    submitbutton.style.backgroundColor = "#ba0000";
                    submitbutton.style.color = "white";
                    document.querySelectorAll('.section hr')[1].innerHTML = "Incorrect";
                }
            }