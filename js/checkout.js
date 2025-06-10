document.addEventListener('DOMContentLoaded', () => {
    const checkoutForm = document.getElementById('checkout-form');
    if (!checkoutForm) return;

    checkoutForm.addEventListener('submit', (event) => {
        event.preventDefault(); // Prevent actual submission

        // Clear previous errors
        document.querySelectorAll('.error-message').forEach(el => el.remove());

        let isValid = true;

        // --- Form Validation ---
        const name = document.getElementById('name');
        if (name.value.trim() === '') {
            isValid = false;
            showError(name, 'نام و نام خانوادگی الزامی است.');
        }

        const email = document.getElementById('email');
        const emailRegex = /^[^\s@]+@[^\s@]+\.[^\s@]+$/;
        if (!emailRegex.test(email.value)) {
            isValid = false;
            showError(email, 'ایمیل معتبر نیست.');
        }
        
        const address = document.getElementById('address');
        if (address.value.trim().length < 10) {
            isValid = false;
            showError(address, 'آدرس باید حداقل ۱۰ کاراکتر باشد.');
        }

        const cardNumber = document.getElementById('card-number');
        if (!/^\d{16}$/.test(cardNumber.value)) {
            isValid = false;
            showError(cardNumber, 'شماره کارت باید ۱۶ رقم باشد.');
        }

        if (isValid) {
            // Simulate successful order
            alert('سفارش شما با موفقیت ثبت شد!');
            
            // Clear the cart
            cart.clearCart();
            
            // Redirect to homepage after a short delay
            setTimeout(() => {
                window.location.href = 'index.html';
            }, 1500);
        }
    });

    function showError(inputElement, message) {
        const errorElement = document.createElement('div');
        errorElement.className = 'error-message';
        errorElement.style.color = '#e74c3c';
        errorElement.style.fontSize = '0.8rem';
        errorElement.style.marginTop = '5px';
        errorElement.textContent = message;
        inputElement.parentElement.appendChild(errorElement);
    }
});
