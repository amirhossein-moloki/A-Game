document.addEventListener('DOMContentLoaded', () => {
    // Load common components like navbar and footer
    loadComponent('components/navbar.html', 'navbar-container');
    loadComponent('components/footer.html', 'footer-container');
});

/**
 * Loads an HTML component from a file into a specified element.
 * @param {string} componentPath - The path to the component HTML file.
 * @param {string} elementId - The ID of the element to load the component into.
 */
async function loadComponent(componentPath, elementId) {
    try {
        const response = await fetch(componentPath);
        if (!response.ok) {
            throw new Error(`Component not found: ${componentPath}`);
        }
        const text = await response.text();
        const element = document.getElementById(elementId);
        if (element) {
            element.innerHTML = text;
            // After loading the navbar, update the cart counter
            if (elementId === 'navbar-container') {
                updateCartCounter();
            }
        }
    } catch (error) {
        console.error('Error loading component:', error);
    }
}

/**
 * Loads products from the JSON file and displays them on the page.
 * @param {string} filterType - (Optional) The type of product to filter by ('account', 'currency', 'digital-game').
 */
async function loadProducts(filterType = 'all') {
    const productListElement = document.getElementById('product-list');
    if (!productListElement) return;

    // Show a loading state
    productListElement.innerHTML = '<p>در حال بارگذاری محصولات...</p>';

    try {
        const response = await fetch('data/products.json');
        if (!response.ok) {
            throw new Error('Could not fetch products data.');
        }
        const data = await response.json();
        const productCardTemplate = await fetch('components/product-card.html').then(res => res.text());
        
        const productsToDisplay = filterType === 'all' 
            ? data.products 
            : data.products.filter(p => p.type === filterType);
            
        if (productsToDisplay.length === 0) {
            productListElement.innerHTML = '<p>محصولی برای نمایش یافت نشد.</p>';
            return;
        }

        productListElement.innerHTML = ''; // Clear loading state
        productsToDisplay.forEach(product => {
            let cardHtml = productCardTemplate;
            cardHtml = cardHtml.replace(/{{id}}/g, product.id)
                               .replace(/{{name}}/g, product.name)
                               .replace(/{{platform}}/g, product.platform)
                               .replace(/{{image}}/g, product.image)
                               .replace(/{{price}}/g, product.price.toLocaleString('fa-IR'))
                               .replace('{{price}}', product.price) // For the addToCart function
                               .replace('{{image}}', product.image); // For the addToCart function
            
            productListElement.innerHTML += cardHtml;
        });
    } catch (error) {
        console.error('Error loading products:', error);
        productListElement.innerHTML = '<p>خطا در بارگذاری محصولات. لطفاً بعداً تلاش کنید.</p>';
    }
}


/**
 * Updates the cart item count displayed in the navbar.
 */
function updateCartCounter() {
    const counterElement = document.getElementById('cart-item-count');
    if (counterElement) {
        const cart = JSON.parse(localStorage.getItem('cart')) || [];
        counterElement.textContent = cart.reduce((sum, item) => sum + item.quantity, 0);
    }
}
