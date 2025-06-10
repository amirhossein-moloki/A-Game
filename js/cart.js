// This script is intended to be a global object `cart`
const cart = {
    /**
     * Adds a product to the cart or increments its quantity.
     * @param {string} id - The product ID.
     * @param {string} name - The product name.
     * @param {number} price - The product price.
     * @param {string} image - The product image URL.
     */
    addToCart(id, name, price, image) {
        let currentCart = this.getCart();
        const existingItem = currentCart.find(item => item.id === id);

        if (existingItem) {
            existingItem.quantity++;
        } else {
            currentCart.push({ id, name, price, image, quantity: 1 });
        }
        
        this._saveCart(currentCart);
        updateCartCounter();
        alert(`'${name}' به سبد خرید اضافه شد.`);
    },

    /**
     * Retrieves the cart from localStorage.
     * @returns {Array} - The array of cart items.
     */
    getCart() {
        return JSON.parse(localStorage.getItem('cart')) || [];
    },

    /**
     * Removes an item completely from the cart.
     * @param {string} id - The ID of the product to remove.
     */
    removeFromCart(id) {
        let currentCart = this.getCart();
        currentCart = currentCart.filter(item => item.id !== id);
        this._saveCart(currentCart);
        // This function should be called from cart.html, which needs to re-render itself
        displayCartItems(); 
        updateCartCounter();
    },

    /**
     * Updates the quantity of a specific item in the cart.
     * @param {string} id - The ID of the product.
     * @param {number} quantity - The new quantity.
     */
    updateQuantity(id, quantity) {
        let currentCart = this.getCart();
        const item = currentCart.find(item => item.id === id);
        
        if (item) {
            item.quantity = Number(quantity);
            if (item.quantity <= 0) {
                // If quantity is 0 or less, remove the item
                this.removeFromCart(id);
                return; // removeFromCart already saves and updates UI
            }
        }

        this._saveCart(currentCart);
        displayCartItems(); // Re-render to show updated total
        updateCartCounter();
    },

    /**
     * Saves the cart to localStorage.
     * @param {Array} cartData - The cart data to save.
     * @private
     */
    _saveCart(cartData) {
        localStorage.setItem('cart', JSON.stringify(cartData));
    },

    /**
     * Clears the entire cart.
     */
    clearCart() {
        localStorage.removeItem('cart');
        if (typeof displayCartItems === 'function') {
            displayCartItems();
        }
        updateCartCounter();
    }
};

/**
 * Renders the cart items on the cart page.
 */
function displayCartItems() {
    const cartItemsContainer = document.getElementById('cart-items-container');
    const cartSummary = document.getElementById('cart-summary');
    if (!cartItemsContainer || !cartSummary) return;

    const currentCart = cart.getCart();
    
    if (currentCart.length === 0) {
        cartItemsContainer.innerHTML = '<p>سبد خرید شما خالی است.</p>';
        cartSummary.style.display = 'none';
        return;
    }

    cartItemsContainer.innerHTML = ''; // Clear previous items
    let total = 0;

    currentCart.forEach(item => {
        total += item.price * item.quantity;
        cartItemsContainer.innerHTML += `
            <div class="cart-item">
                <img src="${item.image}" alt="${item.name}" class="cart-item-image" onerror="this.onerror=null;this.src='https://placehold.co/100x75/1e1e1e/ffffff?text=No+Image';">
                <div class="cart-item-details">
                    <h3>${item.name}</h3>
                    <p>${item.price.toLocaleString('fa-IR')} تومان</p>
                </div>
                <div class="cart-item-quantity">
                    <input type="number" value="${item.quantity}" min="1" onchange="cart.updateQuantity('${item.id}', this.value)">
                </div>
                <button class="remove-from-cart" onclick="cart.removeFromCart('${item.id}')">حذف</button>
            </div>
        `;
    });

    cartSummary.style.display = 'block';
    document.getElementById('cart-total').textContent = `${total.toLocaleString('fa-IR')} تومان`;
}

// If on cart.html, display items on load
if (window.location.pathname.endsWith('cart.html')) {
    document.addEventListener('DOMContentLoaded', displayCartItems);
}
