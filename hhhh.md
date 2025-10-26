1. SSR vs CSR in Next.js
Client-Side Rendering (CSR):

The browser receives a minimal HTML shell and JavaScript bundles
React takes over and renders the entire application in the browser
Initial page load shows a blank screen or loading spinner until JavaScript executes
Subsequent navigation is fast because it happens in the browser
SEO challenges because search engine crawlers may not wait for JavaScript execution

Server-Side Rendering (SSR):

The server generates the complete HTML for each request
Browsers receive fully rendered HTML immediately
Users see content faster (better First Contentful Paint)
JavaScript then "hydrates" the page to make it interactive
Better SEO because crawlers receive complete HTML
In Next.js, implemented using getServerSideProps

Trade-offs:

SSR: Better initial load, SEO-friendly, but slower Time to Interactive (TTI) and higher server load
CSR: Faster subsequent navigation, lower server costs, but worse initial load and SEO
Next.js allows you to choose per-page which rendering strategy fits best


2. Static Site Generation (SSG) and Performance
How SSG Works:

Pages are pre-rendered at build time, not on each request
HTML is generated once and served from a CDN
In Next.js, implemented using getStaticProps and getStaticPaths

Performance Benefits:

Instant Page Loads: Pre-built HTML served directly from CDN edge locations
Reduced Server Load: No server computation per request
Global Distribution: CDN caching means content is geographically close to users
Better Core Web Vitals: Excellent LCP (Largest Contentful Paint) and FID (First Input Delay)
Cost-Effective: Static files are cheaper to host and scale than dynamic servers

Ideal Use Cases:

Blog posts, documentation, marketing pages
E-commerce product pages (with Incremental Static Regeneration)
Any content that doesn't change per-user or changes infrequently

ISR (Incremental Static Regeneration):

Allows updating static pages after build without rebuilding entire site
Set revalidation interval: revalidate: 60 (seconds)
Best of both worlds: static performance with dynamic data freshness


3. TypeScript Advantages in React
Type Safety:

Catches bugs at compile-time before they reach production
Props validation automatically enforced
Prevents common errors like typos in property names

Developer Experience:

IntelliSense: Autocomplete for props, state, and API responses
Refactoring: Rename variables/functions with confidence across entire codebase
Documentation: Types serve as inline documentation
Team Collaboration: Clearer contracts between components

React-Specific Benefits:
typescript// Clear component contracts
interface ButtonProps {
  onClick: () => void;
  disabled?: boolean;
  children: React.ReactNode;
}

// Type-safe hooks
const [count, setCount] = useState<number>(0);

// API response typing
interface User {
  id: string;
  name: string;
  email: string;
}
Reduced Runtime Errors:

TypeScript prevents passing wrong data types
Eliminates "undefined is not a function" errors
Enforces null/undefined checks with strict mode


4. React Reconciliation & Virtual DOM Diffing
The Process:
1. Virtual DOM Creation:

React creates a lightweight JavaScript representation of the DOM
When state/props change, React creates a new Virtual DOM tree

2. Diffing Algorithm:
React compares old and new Virtual DOM trees using a heuristic O(n) algorithm:
Key Heuristics:

Different Types: If root elements are different types (div → span), React destroys old tree and builds new one
Same Type: React keeps the same DOM node and updates only changed attributes
Keys: React uses keys to identify which items changed, were added, or removed

3. Reconciliation Steps:
javascript// Old tree
<ul>
  <li key="1">First</li>
  <li key="2">Second</li>
</ul>

// New tree (item added)
<ul>
  <li key="1">First</li>
  <li key="2">Second</li>
  <li key="3">Third</li>
</ul>

// React identifies: keep 1 & 2, add 3 (efficient)
4. Batch Updates:

React batches multiple setState calls into a single re-render
Minimizes actual DOM manipulations (expensive operations)

5. Commit Phase:

React applies minimal changes to actual DOM
Only updates nodes that actually changed

Why It's Fast:

Direct DOM manipulation is slow
Virtual DOM allows React to calculate minimum necessary changes
Batch updates reduce reflow/repaint cycles


5. Optimizing for Core Web Vitals
LCP (Largest Contentful Paint) - Target: <2.5s
Optimizations:

Image Optimization:

javascript   // Use Next.js Image component
   import Image from 'next/image';
   
   <Image 
     src="/hero.jpg" 
     width={1200} 
     height={600}
     priority // Preload above-fold images
     placeholder="blur"
   />

Server-Side Rendering: Use SSR/SSG for faster initial content
Font Optimization: Use next/font to eliminate font loading delay
Code Splitting: Load only necessary JavaScript initially

FID (First Input Delay) - Target: <100ms
Optimizations:

Reduce JavaScript Execution:

Code splitting with dynamic imports
Remove unused dependencies
Use Web Workers for heavy computations


Optimize Third-Party Scripts:

javascript   import Script from 'next/script';
   
   <Script 
     src="analytics.js" 
     strategy="lazyOnload" // Load after page interactive
   />
CLS (Cumulative Layout Shift) - Target: <0.1
Optimizations:

Always Specify Image/Video Dimensions:

javascript   <Image width={800} height={400} /> // Reserves space

Avoid Inserting Content Above Existing Content:

Use skeleton screens
Reserve space for dynamic content


Use CSS Aspect Ratio: Prevent layout shifts during loading

General Next.js Optimizations:
javascript// next.config.js
module.exports = {
  images: {
    formats: ['image/avif', 'image/webp'],
    deviceSizes: [640, 750, 828, 1080, 1200],
  },
  swcMinify: true, // Faster minification
  compiler: {
    removeConsole: process.env.NODE_ENV === 'production',
  },
}

6. getServerSideProps vs getStaticProps
getStaticProps (Static Generation):
javascriptexport async function getStaticProps(context) {
  const res = await fetch('https://api.example.com/posts');
  const posts = await res.json();
  
  return {
    props: { posts },
    revalidate: 60, // ISR: Regenerate page every 60 seconds
  }
}
When to Use:

Content doesn't change frequently
Content is same for all users
Page can be pre-rendered ahead of user requests
Examples: Blog posts, documentation, product pages

Benefits:

Blazing fast (served from CDN)
No server computation per request
Excellent SEO and performance


getServerSideProps (Server-Side Rendering):
javascriptexport async function getServerSideProps(context) {
  const { req, res, params, query } = context;
  
  // Access cookies, headers
  const token = req.cookies.token;
  
  const data = await fetch(`https://api.example.com/user/${params.id}`, {
    headers: { Authorization: `Bearer ${token}` }
  });
  
  return {
    props: { user: await data.json() },
    // Optional: Cache the response
    // res.setHeader('Cache-Control', 'public, s-maxage=10')
  }
}
When to Use:

Data changes frequently
Content is personalized per-user
Need access to request-time data (cookies, headers)
Cannot pre-render (authentication required)
Examples: User dashboards, personalized feeds

Benefits:

Always fresh data
Access to request context
Still better SEO than CSR

Key Differences:

Execution Time: getStaticProps runs at build time; getServerSideProps runs on every request
Performance: Static is faster (CDN); SSR has server processing delay
Freshness: Static can be stale (use ISR); SSR is always fresh
Cost: Static is cheaper to scale; SSR requires server resources


7. Global State Management
Redux Toolkit:
javascript// store.js
import { configureStore, createSlice } from '@reduxjs/toolkit';

const userSlice = createSlice({
  name: 'user',
  initialState: { profile: null, isLoading: false },
  reducers: {
    setUser: (state, action) => {
      state.profile = action.payload; // Immer allows mutation syntax
    },
    setLoading: (state, action) => {
      state.isLoading = action.payload;
    }
  }
});

export const { setUser, setLoading } = userSlice.actions;

export const store = configureStore({
  reducer: {
    user: userSlice.reducer,
  }
});

// Component usage
import { useSelector, useDispatch } from 'react-redux';

function Profile() {
  const user = useSelector(state => state.user.profile);
  const dispatch = useDispatch();
  
  const updateUser = (data) => {
    dispatch(setUser(data));
  };
}
Benefits:

Strong DevTools for debugging
Middleware support (thunks, sagas)
Time-travel debugging
Great for large, complex applications


Zustand (Lightweight Alternative):
javascript// store.js
import create from 'zustand';
import { persist } from 'zustand/middleware';

export const useStore = create(
  persist(
    (set) => ({
      user: null,
      isLoading: false,
      setUser: (user) => set({ user }),
      setLoading: (isLoading) => set({ isLoading }),
      logout: () => set({ user: null }),
    }),
    {
      name: 'user-storage', // LocalStorage key
    }
  )
);

// Component usage (much simpler!)
function Profile() {
  const user = useStore(state => state.user);
  const setUser = useStore(state => state.setUser);
  
  // Or select multiple
  const { user, setUser, logout } = useStore();
}
Benefits:

Minimal boilerplate
No providers needed
Built-in persistence
Excellent performance (selective subscriptions)
Perfect for small to medium apps

Comparison:

Redux Toolkit: Best for enterprise apps, complex async logic, need for middleware
Zustand: Best for simpler apps, faster development, less boilerplate
Context API: Built-in React solution, good for theme/auth, but performance issues with frequent updates


8. API Calls in Next.js
Native Fetch (Modern Approach):
javascript// In Server Components (Next.js 13+ App Router)
async function Page() {
  const res = await fetch('https://api.example.com/data', {
    cache: 'no-store', // or 'force-cache'
    next: { revalidate: 60 } // ISR
  });
  const data = await res.json();
  
  return <div>{data.title}</div>;
}

// In Client Components
'use client';
import { useEffect, useState } from 'react';

function ClientPage() {
  const [data, setData] = useState(null);
  
  useEffect(() => {
    fetch('/api/data')
      .then(res => res.json())
      .then(setData);
  }, []);
}

Axios (Feature-Rich):
javascriptimport axios from 'axios';

// Create instance with defaults
const api = axios.create({
  baseURL: 'https://api.example.com',
  timeout: 10000,
  headers: { 'Content-Type': 'application/json' }
});

// Interceptors for auth
api.interceptors.request.use(config => {
  const token = localStorage.getItem('token');
  if (token) {
    config.headers.Authorization = `Bearer ${token}`;
  }
  return config;
});

// Error handling
api.interceptors.response.use(
  response => response,
  error => {
    if (error.response?.status === 401) {
      // Redirect to login
    }
    return Promise.reject(error);
  }
);

// Usage
const { data } = await api.get('/users');
await api.post('/users', { name: 'John' });
Benefits:

Automatic JSON transformation
Request/response interceptors
Better error handling
Request cancellation
Progress tracking for uploads


SWR (Data Fetching Hook by Vercel):
javascriptimport useSWR from 'swr';

const fetcher = url => fetch(url).then(r => r.json());

function Profile() {
  const { data, error, isLoading, mutate } = useSWR(
    '/api/user',
    fetcher,
    {
      revalidateOnFocus: true,
      revalidateOnReconnect: true,
      refreshInterval: 0, // Polling interval
    }
  );
  
  if (error) return <div>Failed to load</div>;
  if (isLoading) return <div>Loading...</div>;
  
  // Optimistic UI update
  const updateUser = async (newData) => {
    mutate(newData, false); // Update UI immediately
    await fetch('/api/user', { method: 'PUT', body: JSON.stringify(newData) });
    mutate(); // Revalidate
  };
  
  return <div>{data.name}</div>;
}
Benefits:

Built-in caching
Automatic revalidation
Optimistic UI updates
Deduplication of requests
Pagination and infinite loading support
Focus tracking and network status revalidation


React Query (TanStack Query) - Most Powerful:
javascriptimport { useQuery, useMutation, useQueryClient } from '@tanstack/react-query';

function Users() {
  const queryClient = useQueryClient();
  
  // Fetch data
  const { data, isLoading, error } = useQuery({
    queryKey: ['users'],
    queryFn: () => fetch('/api/users').then(r => r.json()),
    staleTime: 5000, // Consider data fresh for 5s
    cacheTime: 10 * 60 * 1000, // Keep in cache for 10min
  });
  
  // Mutations
  const mutation = useMutation({
    mutationFn: (newUser) => fetch('/api/users', {
      method: 'POST',
      body: JSON.stringify(newUser),
    }),
    onSuccess: () => {
      queryClient.invalidateQueries({ queryKey: ['users'] });
    },
  });
  
  return (
    <button onClick={() => mutation.mutate({ name: 'New User' })}>
      Add User
    </button>
  );
}
Recommendation:

Simple projects: Native fetch
Need interceptors/config: Axios
Real-time data: SWR or React Query
Complex data needs: React Query (best caching, background updates)


9. Tailwind CSS Benefits
Utility-First Advantages:
1. Rapid Development:
jsx// Traditional CSS
<button className="custom-button primary-button">Click</button>
// Requires separate CSS file with .custom-button {...}

// Tailwind
<button className="bg-blue-500 hover:bg-blue-600 text-white px-4 py-2 rounded">
  Click
</button>
// Styled directly in markup, no context switching
2. No CSS Bloat:

PurgeCSS removes unused styles in production
Final CSS bundle is tiny (often <10KB)
Traditional CSS grows as project grows

3. Consistency:
jsx// Design system built-in
className="text-lg" // Always 1.125rem
className="p-4" // Always 1rem padding
className="bg-blue-500" // Always same shade

// Prevents: font-size: 1.123rem, padding: 17px (random values)
4. Responsive Design:
jsx<div className="w-full md:w-1/2 lg:w-1/3">
  {/* Mobile: full width, Tablet: half, Desktop: third */}
</div>
5. No Naming Fatigue:

No need to invent class names (.hero-section-primary-button-large)
No BEM complexity
No specificity wars

6. Easy Theme Customization:
javascript// tailwind.config.js
module.exports = {
  theme: {
    extend: {
      colors: {
        brand: '#FF6B6B',
      }
    }
  }
}

// Use: className="bg-brand"
7. Performance:

Smaller bundle size than Bootstrap/MaterialUI
Atomic CSS = high reusability
No runtime JavaScript (unlike styled-components)

Comparison with CSS Modules:

CSS Modules: Scoped styles, but still write CSS separately
Tailwind: Faster, no context switching, built-in design system
Both prevent global namespace pollution


10. Responsive Design with Tailwind
Breakpoint System:
jsx<div className="
  text-sm          // Base (mobile-first)
  md:text-base     // ≥768px
  lg:text-lg       // ≥1024px
  xl:text-xl       // ≥1280px
  2xl:text-2xl     // ≥1536px
">
  Responsive Text
</div>
Mobile-First Philosophy:

Default styles apply to all sizes
Add prefixes for larger screens
Reduces CSS bloat


Layout Patterns:
1. Responsive Grid:
jsx<div className="
  grid 
  grid-cols-1        // 1 column on mobile
  md:grid-cols-2     // 2 columns on tablet
  lg:grid-cols-3     // 3 columns on desktop
  gap-4
">
  <Card />
  <Card />
  <Card />
</div>
2. Flex Layouts:
jsx<nav className="
  flex 
  flex-col           // Vertical on mobile
  md:flex-row        // Horizontal on tablet+
  items-center 
  justify-between
  gap-4
">
  <Logo />
  <Menu />
</nav>
3. Hiding Elements:
jsx<div className="hidden md:block">Desktop Only</div>
<div className="md:hidden">Mobile Only</div>
4. Container with Max Width:
jsx<div className="
  container          // Centers content
  mx-auto           // Horizontal margin auto
  px-4              // Padding on mobile
  md:px-6           // More padding on tablet
  lg:px-8           // Even more on desktop
">
  Content
</div>

Advanced Techniques:
Custom Breakpoints:
javascript// tailwind.config.js
module.exports = {
  theme: {
    screens: {
      'tablet': '640px',
      'laptop': '1024px',
      'desktop': '1280px',
    }
  }
}

// Usage: className="tablet:text-lg laptop:text-xl"
Arbitrary Values:
jsx<div className="w-[347px] md:w-[600px]">
  {/* Custom widths when needed */}
</div>
Group Hover (Parent-Child Interaction):
jsx<div className="group">
  <img className="group-hover:opacity-75" />
  <div className="opacity-0 group-hover:opacity-100">
    Overlay appears on hover
  </div>
</div>
Dark Mode:
jsx<div className="bg-white dark:bg-gray-900 text-black dark:text-white">
  Adapts to system preference
</div>

11. useEffect vs useLayoutEffect
useEffect (Most Common):
javascriptuseEffect(() => {
  // Runs AFTER browser paints
  fetchData();
  document.title = 'New Title';
}, [dependencies]);
Timing:

Component renders
Browser paints to screen
useEffect runs asynchronously

Use Cases:

Data fetching
Setting up subscriptions
Logging/analytics
Most side effects

Benefits:

Non-blocking (better performance)
User sees updates faster


useLayoutEffect (Synchronous):
javascriptuseLayoutEffect(() => {
  // Runs BEFORE browser paints
  // Measure DOM elements
  const height = elementRef.current.offsetHeight;
  setHeight(height);
}, [dependencies]);
Timing:

Component renders
useLayoutEffect runs synchronously
Browser paints (with updated DOM)

Use Cases:

DOM measurements (getBoundingClientRect)
Scroll position manipulation
Animations that need to synchronize with paint
Preventing visual flicker


Example - When useLayoutEffect is Necessary:
javascript// ❌ BAD: Visual flicker
function Tooltip() {
  const [position, setPosition] = useState({ x: 0, y: 0 });
  
  useEffect(() => {
    // Browser paints tooltip at (0,0) first
    // Then moves it (user sees flicker)
    const rect = tooltipRef.current.getBoundingClientRect();
    setPosition(calculatePosition(rect));
  }, []);
  
  return <div ref={tooltipRef} style={position}>Tooltip</div>;
}

// ✅ GOOD: No flicker
function Tooltip() {
  const [position, setPosition] = useState({ x: 0, y: 0 });
  
  useLayoutEffect(() => {
    // Position calculated BEFORE paint
    // User never sees tooltip at wrong position
    const rect = tooltipRef.current.getBoundingClientRect();
    setPosition(calculatePosition(rect));
  }, []);
  
  return <div ref={tooltipRef} style={position}>Tooltip</div>;
}
Warning:

useLayoutEffect blocks painting (can cause performance issues)
Use only when visual consistency is critical
99% of the time, useEffect is correct choice


12. Securing Environment Variables
Next.js Environment Variables:
1. Server-Side Only (Secure):
bash# .env.local
DATABASE_URL=postgresql://...
API_SECRET_KEY=sk_live_...
STRIPE_SECRET_KEY=sk_test_...

# These NEVER go to browser
# Access in getServerSideProps, API routes, Server Components
2. Client-Side (Public):
bash# Must prefix with NEXT_PUBLIC_
NEXT_PUBLIC_API_URL=https://api.example.com
NEXT_PUBLIC_ANALYTICS_ID=GA-123456

# These ARE exposed in browser bundle
# Only use for non-sensitive data

Best Practices:
1. Never Commit Secrets:
bash# .gitignore
.env.local
.env.development.local
.env.production.local
```

**2. Environment-Specific Files:**
```
.env.local          # Local development (gitignored)
.env.development    # Development defaults (can commit)
.env.production     # Production config (deploy platform)
3. Use API Routes as Proxy:
javascript// pages/api/stripe.js (server-side)
export default async function handler(req, res) {
  const stripe = require('stripe')(process.env.STRIPE_SECRET_KEY);
  
  const session = await stripe.checkout.sessions.create({...});
  res.json({ sessionId: session.id });
}

// Client-side
fetch('/api/stripe').then(r => r.json());
// Secret key never exposed
4. Deployment Platforms:

Vercel: Add variables in Project Settings
Netlify: Environment variables in Site Settings
AWS: Use Secrets Manager or Parameter Store

5. Validation:
javascript// lib/env.js
const requiredEnvVars = [
  'DATABASE_URL',
  'NEXT_PUBLIC_API_URL',
];

requiredEnvVars.forEach(varName => {
  if (!process.env[varName]) {
    throw new Error(`Missing required environment variable: ${varName}`);
  }
});
6. Type Safety:
typescript// env.d.ts
declare global {
  namespace NodeJS {
    interface ProcessEnv {
      DATABASE_URL: string;
      NEXT_PUBLIC_API_URL: string;
      STRIPE_SECRET_KEY: string;
    }
  }
}

13. Reducing Bundle Size
1. Dynamic Imports (Code Splitting):
javascript// ❌ BAD: Loads immediately
import HeavyChart from 'react-charts';

// ✅ GOOD: Loads only when needed
import dynamic from 'next/dynamic';

const HeavyChart = dynamic(() => import('react-charts'), {
  loading: () => <p>Loading chart...</p>,
  ssr: false // Don't render on server
});

// Or with React.lazy
const HeavyChart = lazy(() => import('react-charts'));
2. Analyze Bundle:
bashnpm install --save-dev @next/bundle-analyzer

# next.config.js
const withBundleAnalyzer = require('@next/bundle-analyzer')({
  enabled: process.env.ANALYZE === 'true',
});

module.exports = withBundleAnalyzer({...});

# Run: ANALYZE=true npm run build
3. Tree Shaking (Import Specific Modules):
javascript// ❌ BAD: Imports entire lodash (70KB)
import _ from 'lodash';
_.debounce(fn, 300);

// ✅ GOOD: Imports only debounce (~2KB)
import debounce from 'lodash/debounce';
debounce(fn, 300);

// Or use ES modules version
import { debounce } from 'lodash-es';
4. Remove Unused Dependencies:
bashnpm install -g depcheck
depcheck
# Remove packages that aren't used
5. Optimize Images:
javascriptimport Image from 'next/image';

<Image 
  src="/large-image.jpg"
  width={800}
  height={600}
  quality={75} // Default 75 is good balance
  loading="lazy" // Lazy load off-screen images
/>
6. Use Modern Build Tools:
javascript// next.config.js
module.exports = {
  swcMinify: true, // Faster than Terser
  compiler: {
    removeConsole: process.env.NODE_ENV === 'production',
  },
}
7. Lazy Load Non-Critical CSS:
javascript// Critical CSS inline, defer non-critical
<link rel="preload" href="/critical.css" as="style" />
<link rel="stylesheet" href="/non-critical.css" media="print" onload="this.media='all'" />
8. Use Lighter Alternatives:

date-fns instead of moment.js (saves ~50KB)
axios → native fetch (saves ~15KB)
lodash → native ES6 methods when possible

9. Polyfill Only What's Needed:
javascript// next.config.js
module.exports = {
  experimental: {
    modern BuildTarget: true, // Skips polyfills for modern browsers
  },
}
```

---

## 14. Dynamic Routing in Next.js

**File-Based Routing:**

**1. Simple Dynamic Routes:**
```
pages/
  posts/
    [id].js        → /posts/123
    [slug].js      → /posts/my-post
javascript// pages/posts/[id].js
import { useRouter } from 'next/router';

export default function Post() {
  const router = useRouter();
  const { id } = router.query; // Access dynamic parameter
  
  return <div>Post ID: {id}</div>;
}

// With getStaticProps
export async function getStaticPaths() {
  // Define which paths to pre-render
  return {
    paths: [
      { params: { id: '1' } },
      { params: { id: '2' } },
    ],
    fallback: 'blocking', // or false, true
  };
}

export async function getStaticProps({ params }) {
  const post = await fetchPost(params.id);
  return { props: { post } };
}
```

**2. Catch-All Routes:**
```
pages/
  docs/
    [...slug].js   → /docs/a, /docs/a/b, /docs/a/b/c
javascript// pages/docs/[...slug].js
export default function Docs() {
  const router = useRouter();
  const { slug } = router.query;
  // slug is an array: /docs/a/b/c → ['a', 'b', 'c']
  
  return <div>Path: {slug?.join('/')}</div>;
}
```

**3. Optional Catch-All:**
```
pages/
  shop/
    [[...slug]].js → /shop, /shop/electronics, /shop/electronics/phones
```

**4. Multiple Dynamic Segments:**
```
pages/
  [category]/
    [product]/
      [variant].js → /shoes/nike/red-size-10
```

---

**App Router (Next.js 13+):**
```
app/
  posts/
    [id]/
      page.tsx     → /posts/123
      
export default function Post({ params }) {
  return <div>Post: {params.id}</div>;
}

// Generate static params
export async function generateStaticParams() {
  const posts = await fetchPosts();
  return posts.map(post => ({  id: post.id }));
}
Programmatic Navigation:
javascriptimport { useRouter } from 'next/router';

function Component() {
  const router = useRouter();
  
  // Navigate
  router.push('/posts/123');
  router.push({
    pathname: '/posts/[id]',
    query: { id: 123 },
  });
  
  // Replace (no history entry)
  router.replace('/posts/123');
  
  // Go back
  router.back();
}

15. Hydration in Next.js
What is Hydration?
The process where React attaches event listeners and makes server-rendered HTML interactive.
The Process:
1. Server-Side:
javascript// Server generates HTML
<button class="px-4 py-2">Click Me</button>
// Sent to browser (non-interactive)
2. Browser Receives HTML:

User sees content immediately (fast First Contentful Paint)
But buttons don't work yet (no JavaScript)

3. JavaScript Loads:
javascript// React bundle downloads and executes
// React "hydrates" the existing HTML
4. Hydration:
javascript// React attaches event listeners
<button onClick={handleClick}>Click Me</button>
// Now interactive!

Hydration Mismatches (Common Errors):
javascript// ❌RetryClaude does not have the ability to run the code it generates yet.TIContinuejavascript// ❌ BAD: Server and client render different content
function Component() {
  const [mounted, setMounted] = useState(false);
  
  // Server renders: "Server time: undefined"
  // Client renders: "Server time: 3:45 PM"
  // MISMATCH ERROR!
  return <div>Server time: {new Date().toLocaleTimeString()}</div>;
}

// ✅ GOOD: Render same content, then update
function Component() {
  const [time, setTime] = useState(null);
  
  useEffect(() => {
    // Only runs on client after hydration
    setTime(new Date().toLocaleTimeString());
  }, []);
  
  return <div>Server time: {time || 'Loading...'}</div>;
}
Common Causes of Mismatches:

Using browser-only APIs during SSR (localStorage, window)
Random values (Math.random(), Date.now())
Conditional rendering based on client state
Third-party scripts injecting content

Preventing Mismatches:
javascript// Check if running on client
if (typeof window !== 'undefined') {
  // Safe to use browser APIs
}

// Or use dynamic imports with ssr: false
const ClientOnlyComponent = dynamic(
  () => import('./ClientOnly'),
  { ssr: false }
);

Selective Hydration (React 18+):
React can prioritize which components to hydrate first based on user interaction:
javascript// User clicks button before full hydration
// React prioritizes hydrating that component first
Benefits:

Faster Time to Interactive (TTI)
Page feels responsive sooner
Better user experience on slow connections


16. Lazy Loading Implementation
1. Component Lazy Loading:
javascript// React.lazy (Client Components)
import { lazy, Suspense } from 'react';

const HeavyComponent = lazy(() => import('./HeavyComponent'));

function Page() {
  return (
    <Suspense fallback={<div>Loading...</div>}>
      <HeavyComponent />
    </Suspense>
  );
}

// Next.js dynamic imports
import dynamic from 'next/dynamic';

const DynamicComponent = dynamic(() => import('./Heavy'), {
  loading: () => <Skeleton />,
  ssr: false, // Don't render on server
});

// Load only when visible
const LazyModal = dynamic(() => import('./Modal'), {
  suspense: true,
});

function App() {
  const [showModal, setShowModal] = useState(false);
  
  return (
    <>
      <button onClick={() => setShowModal(true)}>Open</button>
      {showModal && (
        <Suspense fallback={<div>Loading modal...</div>}>
          <LazyModal />
        </Suspense>
      )}
    </>
  );
}

2. Image Lazy Loading:
javascript// Next.js Image component (automatic lazy loading)
import Image from 'next/image';

<Image 
  src="/large-image.jpg"
  width={800}
  height={600}
  loading="lazy" // Default for images below fold
  placeholder="blur" // Show blur while loading
  blurDataURL="data:image/..." // Or use automatic blur
/>

// Native HTML (modern browsers)
<img 
  src="image.jpg" 
  loading="lazy" 
  decoding="async"
/>
Advanced Image Techniques:
javascript// Intersection Observer for custom lazy loading
import { useEffect, useRef, useState } from 'react';

function LazyImage({ src, alt }) {
  const [isVisible, setIsVisible] = useState(false);
  const imgRef = useRef();
  
  useEffect(() => {
    const observer = new IntersectionObserver(
      ([entry]) => {
        if (entry.isIntersecting) {
          setIsVisible(true);
          observer.disconnect();
        }
      },
      { rootMargin: '100px' } // Start loading 100px before visible
    );
    
    if (imgRef.current) {
      observer.observe(imgRef.current);
    }
    
    return () => observer.disconnect();
  }, []);
  
  return (
    <img
      ref={imgRef}
      src={isVisible ? src : '/placeholder.jpg'}
      alt={alt}
    />
  );
}
```

---

**3. Route-Based Code Splitting:**

Next.js automatically splits code by route:
```
pages/
  index.js        → bundle: index-[hash].js
  about.js        → bundle: about-[hash].js
  posts/[id].js   → bundle: [id]-[hash].js
Each page only loads its required JavaScript.

4. Library Lazy Loading:
javascript// Load heavy library only when needed
async function handleExport() {
  // xlsx library not loaded until export clicked
  const XLSX = await import('xlsx');
  const workbook = XLSX.utils.book_new();
  // ... export logic
}

<button onClick={handleExport}>Export to Excel</button>

5. Lazy Loading with Intersection Observer:
javascript// For lists, carousels, infinite scroll
function InfiniteScroll() {
  const [items, setItems] = useState([]);
  const [page, setPage] = useState(1);
  const loaderRef = useRef(null);
  
  useEffect(() => {
    const observer = new IntersectionObserver(
      (entries) => {
        if (entries[0].isIntersecting) {
          loadMore();
        }
      },
      { threshold: 0.5 }
    );
    
    if (loaderRef.current) {
      observer.observe(loaderRef.current);
    }
    
    return () => observer.disconnect();
  }, []);
  
  const loadMore = async () => {
    const newItems = await fetchItems(page);
    setItems(prev => [...prev, ...newItems]);
    setPage(prev => prev + 1);
  };
  
  return (
    <>
      {items.map(item => <Item key={item.id} data={item} />)}
      <div ref={loaderRef}>Loading more...</div>
    </>
  );
}

6. Font Lazy Loading:
javascript// next.config.js with next/font
import { Inter, Roboto_Mono } from 'next/font/google';

const inter = Inter({
  subsets: ['latin'],
  display: 'swap', // Avoid invisible text while loading
  preload: true, // Preload critical fonts
});

const robotoMono = Roboto_Mono({
  subsets: ['latin'],
  display: 'swap',
  preload: false, // Lazy load non-critical fonts
});
Benefits of Lazy Loading:

Faster initial page load
Reduced bandwidth usage
Better Core Web Vitals
Improved user experience (progressive loading)


17. SEO Optimization in Next.js
1. Meta Tags with next/head:
javascriptimport Head from 'next/head';

function Page({ post }) {
  return (
    <>
      <Head>
        <title>{post.title} | My Blog</title>
        <meta name="description" content={post.excerpt} />
        
        {/* Open Graph (Facebook, LinkedIn) */}
        <meta property="og:title" content={post.title} />
        <meta property="og:description" content={post.excerpt} />
        <meta property="og:image" content={post.imageUrl} />
        <meta property="og:url" content={`https://example.com/posts/${post.slug}`} />
        <meta property="og:type" content="article" />
        
        {/* Twitter Card */}
        <meta name="twitter:card" content="summary_large_image" />
        <meta name="twitter:title" content={post.title} />
        <meta name="twitter:description" content={post.excerpt} />
        <meta name="twitter:image" content={post.imageUrl} />
        
        {/* Canonical URL */}
        <link rel="canonical" href={`https://example.com/posts/${post.slug}`} />
        
        {/* Structured Data (JSON-LD) */}
        <script
          type="application/ld+json"
          dangerouslySetInnerHTML={{
            __html: JSON.stringify({
              "@context": "https://schema.org",
              "@type": "BlogPosting",
              "headline": post.title,
              "description": post.excerpt,
              "image": post.imageUrl,
              "author": {
                "@type": "Person",
                "name": post.author
              },
              "datePublished": post.publishedAt,
            })
          }}
        />
      </Head>
      
      <article>{/* Content */}</article>
    </>
  );
}

2. App Router Metadata (Next.js 13+):
javascript// app/posts/[slug]/page.tsx
import { Metadata } from 'next';

export async function generateMetadata({ params }): Promise<Metadata> {
  const post = await getPost(params.slug);
  
  return {
    title: post.title,
    description: post.excerpt,
    openGraph: {
      title: post.title,
      description: post.excerpt,
      images: [post.imageUrl],
      type: 'article',
    },
    twitter: {
      card: 'summary_large_image',
      title: post.title,
      description: post.excerpt,
      images: [post.imageUrl],
    },
    alternates: {
      canonical: `https://example.com/posts/${params.slug}`,
    },
  };
}

3. Sitemap Generation:
javascript// pages/sitemap.xml.js
export async function getServerSideProps({ res }) {
  const posts = await getAllPosts();
  
  const sitemap = `<?xml version="1.0" encoding="UTF-8"?>
    <urlset xmlns="http://www.sitemaps.org/schemas/sitemap/0.9">
      <url>
        <loc>https://example.com</loc>
        <changefreq>daily</changefreq>
        <priority>1.0</priority>
      </url>
      ${posts.map(post => `
        <url>
          <loc>https://example.com/posts/${post.slug}</loc>
          <lastmod>${post.updatedAt}</lastmod>
          <changefreq>weekly</changefreq>
          <priority>0.8</priority>
        </url>
      `).join('')}
    </urlset>
  `;
  
  res.setHeader('Content-Type', 'text/xml');
  res.write(sitemap);
  res.end();
  
  return { props: {} };
}

export default function Sitemap() {}

4. Robots.txt:
javascript// pages/robots.txt.js
export async function getServerSideProps({ res }) {
  const robots = `User-agent: *
Allow: /
Disallow: /api/
Disallow: /admin/

Sitemap: https://example.com/sitemap.xml
  `;
  
  res.setHeader('Content-Type', 'text/plain');
  res.write(robots);
  res.end();
  
  return { props: {} };
}

export default function Robots() {}

5. Semantic HTML:
javascriptfunction Article({ post }) {
  return (
    <article itemScope itemType="https://schema.org/BlogPosting">
      <header>
        <h1 itemProp="headline">{post.title}</h1>
        <time itemProp="datePublished" dateTime={post.publishedAt}>
          {formatDate(post.publishedAt)}
        </time>
        <address itemProp="author" itemScope itemType="https://schema.org/Person">
          <span itemProp="name">{post.author}</span>
        </address>
      </header>
      
      <div itemProp="articleBody">
        {post.content}
      </div>
    </article>
  );
}

6. Image Optimization for SEO:
javascript<Image
  src="/product.jpg"
  alt="Red Nike Running Shoes - Size 10" // Descriptive alt text
  width={800}
  height={600}
  priority // For above-fold images
/>

// Also optimize filenames: product-red-nike-shoes.jpg
// Not: IMG_1234.jpg

7. Performance = SEO:

Google uses Core Web Vitals as ranking factor
Use SSG/SSR for instant content visibility
Optimize images, fonts, JavaScript
Minimize CLS (layout shifts)


8. Internal Linking:
javascriptimport Link from 'next/link';

<Link href="/related-post" prefetch={true}>
  Read more about React optimization
</Link>
// Descriptive anchor text helps SEO

9. International SEO (i18n):
javascript// next.config.js
module.exports = {
  i18n: {
    locales: ['en', 'es', 'fr'],
    defaultLocale: 'en',
  },
}

// Automatic hreflang tags
<link rel="alternate" hreflang="en" href="https://example.com/en/page" />
<link rel="alternate" hreflang="es" href="https://example.com/es/page" />

18. Frontend Testing Tools
1. Jest (Unit Testing):
javascript// component.test.js
import { render, screen } from '@testing-library/react';
import Button from './Button';

describe('Button Component', () => {
  test('renders button with correct text', () => {
    render(<Button>Click Me</Button>);
    const button = screen.getByRole('button', { name: /click me/i });
    expect(button).toBeInTheDocument();
  });
  
  test('calls onClick handler when clicked', () => {
    const handleClick = jest.fn();
    render(<Button onClick={handleClick}>Click</Button>);
    
    const button = screen.getByRole('button');
    button.click();
    
    expect(handleClick).toHaveBeenCalledTimes(1);
  });
  
  test('is disabled when disabled prop is true', () => {
    render(<Button disabled>Click</Button>);
    const button = screen.getByRole('button');
    expect(button).toBeDisabled();
  });
});

// Testing hooks
import { renderHook, act } from '@testing-library/react';
import useCounter from './useCounter';

test('should increment counter', () => {
  const { result } = renderHook(() => useCounter());
  
  act(() => {
    result.current.increment();
  });
  
  expect(result.current.count).toBe(1);
});
Jest Configuration:
javascript// jest.config.js
module.exports = {
  testEnvironment: 'jsdom',
  setupFilesAfterEnv: ['<rootDir>/jest.setup.js'],
  moduleNameMapper: {
    '^@/(.*)$': '<rootDir>/src/$1',
    '\\.(css|less|scss)$': 'identity-obj-proxy',
  },
  coverageThreshold: {
    global: {
      branches: 80,
      functions: 80,
      lines: 80,
    },
  },
};

2. React Testing Library (Component Testing):
javascriptimport { render, screen, waitFor, fireEvent } from '@testing-library/react';
import userEvent from '@testing-library/user-event';
import UserProfile from './UserProfile';

test('displays user data after loading', async () => {
  // Mock API
  global.fetch = jest.fn(() =>
    Promise.resolve({
      json: () => Promise.resolve({ name: 'John', email: 'john@example.com' }),
    })
  );
  
  render(<UserProfile userId="123" />);
  
  // Initially shows loading
  expect(screen.getByText(/loading/i)).toBeInTheDocument();
  
  // Wait for data to load
  await waitFor(() => {
    expect(screen.getByText('John')).toBeInTheDocument();
  });
  
  expect(screen.getByText('john@example.com')).toBeInTheDocument();
});

test('handles form submission', async () => {
  const user = userEvent.setup();
  const onSubmit = jest.fn();
  
  render(<ContactForm onSubmit={onSubmit} />);
  
  // Type in form fields
  await user.type(screen.getByLabelText(/name/i), 'John Doe');
  await user.type(screen.getByLabelText(/email/i), 'john@example.com');
  
  // Submit form
  await user.click(screen.getByRole('button', { name: /submit/i }));
  
  expect(onSubmit).toHaveBeenCalledWith({
    name: 'John Doe',
    email: 'john@example.com',
  });
});
Best Practices:

Query by role/label (accessibility-focused)
Avoid testing implementation details
Test user behavior, not internal state
Use userEvent instead of fireEvent for realistic interactions


3. Cypress (E2E Testing):
javascript// cypress/e2e/login.cy.js
describe('Login Flow', () => {
  beforeEach(() => {
    cy.visit('/login');
  });
  
  it('should login successfully with valid credentials', () => {
    cy.get('[data-testid="email-input"]').type('user@example.com');
    cy.get('[data-testid="password-input"]').type('password123');
    cy.get('[data-testid="submit-button"]').click();
    
    // Assert redirect
    cy.url().should('include', '/dashboard');
    cy.contains('Welcome back!').should('be.visible');
  });
  
  it('should show error with invalid credentials', () => {
    cy.get('[data-testid="email-input"]').type('wrong@example.com');
    cy.get('[data-testid="password-input"]').type('wrongpass');
    cy.get('[data-testid="submit-button"]').click();
    
    cy.contains('Invalid credentials').should('be.visible');
    cy.url().should('include', '/login'); // Stay on login page
  });
  
  it('should persist login after page refresh', () => {
    cy.login('user@example.com', 'password123'); // Custom command
    cy.reload();
    cy.url().should('include', '/dashboard');
  });
});

// cypress/support/commands.js
Cypress.Commands.add('login', (email, password) => {
  cy.visit('/login');
  cy.get('[data-testid="email-input"]').type(email);
  cy.get('[data-testid="password-input"]').type(password);
  cy.get('[data-testid="submit-button"]').click();
  cy.url().should('include', '/dashboard');
});

// API mocking
cy.intercept('POST', '/api/login', {
  statusCode: 200,
  body: { token: 'fake-token', user: { name: 'John' } },
}).as('loginRequest');

cy.wait('@loginRequest');

